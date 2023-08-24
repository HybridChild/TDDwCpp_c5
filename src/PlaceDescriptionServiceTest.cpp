#include "gmock/gmock.h"

#include <vector>

#include "PlaceDescriptionService.h"
#include "Http.h"

using namespace std;
using namespace testing;

class APlaceDescriptionService: public Test {
public:
   static const string ValidLatitude;
   static const string ValidLongitude;
};

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");

// START:HttpStub
class HttpStub: public Http
{
public:
   MOCK_METHOD0(initialize, void());
   MOCK_CONST_METHOD1(get, string(const string&));
};
// END:HttpStub

TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress)
{
   HttpStub httpStub;
   
   string urlStart("http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");
   auto expectedURL =
      urlStart +
      "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
      "lon=" + APlaceDescriptionService::ValidLongitude;
   
   EXPECT_CALL(httpStub, initialize());            // tell GoogleMock to expect a call to initialize()
   EXPECT_CALL(httpStub, get(expectedURL));        // tell GoogleMock to expect a call to get() with the expectedURL
   PlaceDescriptionService service{&httpStub};
   service.summaryDescription(ValidLatitude, ValidLongitude);

   Mock::VerifyAndClearExpectations(&httpStub);    // optional: httpStub will be verified when it goes out of scope
}

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription)
{
   NiceMock<HttpStub> httpStub;     // NiceMock allows us to ignore calls to functions we don't care about
   EXPECT_CALL(httpStub, get(_))    // the _ wildcard allows GoogleMock to match on any call to the function regardless of the argument
      .WillOnce(Return(             // tell GoogleMock what to return from a call to get()
         R"({ "address": {
                  "road":"Drury Ln",
                  "city":"Fountain",
                  "state":"CO",
                  "country":"US" 
         }})"
      ));
   PlaceDescriptionService service(&httpStub);
   auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
   ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
