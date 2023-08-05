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
   auto jsonResponse = get(requestUrl);
   return summaryDescription(jsonResponse);
}

string PlaceDescriptionService::createGetRequestUrl( const string& latitude, const string& longitude) const
{
   string server{"http://open.mapquestapi.com/"};
   string document{"nominatim/v1/reverse"};

   return server + document + "?" +
      keyValue("format", "json") + "&" +
      keyValue("lat", latitude) + "&" +
      keyValue("lon", longitude);
}

string PlaceDescriptionService::get(const string& requestUrl) const
{
   return http_->get(requestUrl);
}

string PlaceDescriptionService::summaryDescription(const string& jsonResponse) const
{
   AddressExtractor extractor;
   auto address = extractor.addressFrom(jsonResponse);
   
   return address.road + ", " + address.city + ", " + 
          address.state + ", " + address.country;
}

string PlaceDescriptionService::keyValue(const string& key, const string& value) const
{
   return key + "=" + value;
}
