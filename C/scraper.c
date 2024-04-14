#include <stdio.h>
#include "scraper.h"


int main(void)
{
    /*initialize curl globally*/
    curl_global_init(CURL_GLOBAL_ALL);
        
    /* initialize a CURL instance*/
    CURL *curl_handle = curl_easy_init();
    
    /*retrieve the HTML document of the target page*/
    struct CURLResponse response = GetRequest(curl_handle, "https://scrapeme.live/shop/");
    /*print the HTML content*/
    printf("%s\n", response.html);
    
    /*scraping logic...*/
    
    /*cleanup the curl instance*/
    curl_easy_cleanup(curl_handle);
    /*cleanup the curl resources*/
    curl_global_cleanup();
    
    return (0);
}