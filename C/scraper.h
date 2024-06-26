#define __SCRAPER_H__
#ifndef __SCRAPER_H__

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <curl/curl.libcurl.h>
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"


struct CURLResponse
{
    char *html;
    size_t size;
};
    
static size_t WriteHTMLCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct CURLResponse *mem = (struct CURLResponse *)userp;
    char *ptr = realloc(mem->html, mem->size + realsize + 1);
  
    if (!ptr)
    {
        printf("Not enough memory available (realloc returned NULL)\n");
        return 0;
    }
      
    mem->html = ptr;
    memcpy(&(mem->html[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->html[mem->size] = 0;

    return realsize;
}
    
struct CURLResponse GetRequest(CURL *curl_handle, const char *url)
{
    CURLcode res;
    struct CURLResponse response;
      
    // initialize the response
    response.html = malloc(1);
    response.size = 0;
      
    // specify URL to GET
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    // send all data returned by the server to WriteHTMLCallback
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteHTMLCallback);
    // pass "response" to the callback function
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&response);
    // set a User-Agent header
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36");
    // perform the GET request
    res = curl_easy_perform(curl_handle);

    // check for HTTP errors
    if (res != CURLE_OK)
    {
        fprintf(stderr, "GET request failed: %s\n", curl_easy_strerror(res));
    }
  
    return response;
}


#endif /* __SCRAPER_H__ Header file structure.*/ 