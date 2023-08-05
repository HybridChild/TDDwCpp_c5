#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
#include <string>

using namespace std;

PlaceDescriptionService::PlaceDescriptionService(Http* http) : http_(http) {}

string PlaceDescriptionService::summaryDescription(const string& latitude, const string& longitude) const
{
   auto requestUrl = createGetRequestUrl(latitude, longitude);
   auto jsonResponse = http_->get(requestUrl);

   AddressExtractor extractor;
   auto address = extractor.addressFrom(jsonResponse);

   return summaryDescription(address);
}

string PlaceDescriptionService::createGetRequestUrl( const string& latitude, const string& longitude) const
{
   return "lat=" + latitude + "&" + "lon=" + longitude;
}

string PlaceDescriptionService::summaryDescription(const Address& address) const {
   return address.road + ", " + address.city + ", " + 
          address.state + ", " + address.country;
}

