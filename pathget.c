#include <stdio.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
    // Check if an argument is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 1;
    }

    CURL *curl;
    CURLcode res;
    long response_code;
    double response_size;

    // Initialize libcurl
    curl = curl_easy_init();
    if (curl) {
        // Define a buffer to store the full URL
        char url[256];
        
        // Create the full URL using snprintf
        snprintf(url, sizeof(url), "https://acas.edu.bd/%s", argv[1]);

        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Set custom headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "origin: https://acas.edu.bd");
        headers = curl_slist_append(headers, "referer: https://acas.edu.bd/");
        headers = curl_slist_append(headers, "sec-ch-ua: \"Chromium\";v=\"130\", \"Brave\";v=\"130\", \"Not?A_Brand\";v=\"99\"");
        headers = curl_slist_append(headers, "sec-ch-ua-mobile: ?0");
        headers = curl_slist_append(headers, "sec-ch-ua-platform: \"Windows\"");
        headers = curl_slist_append(headers, "user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36");

        // Attach headers to the request
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res == CURLE_OK) {
            // Get the HTTP status code
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

            // Get the size of the response
            curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &response_size);

            // Print status code and response size
            printf("\n");
            printf("XXXXXXXXXXXXXXXXXXXX\n");
            printf("%s\n",argv[1]);
            printf("Status Code: %ld\n", response_code);
            printf("Response Size: %.0f bytes\n", response_size);
            printf("======================\n");
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Clean up
        curl_slist_free_all(headers); // Free the header list
        curl_easy_cleanup(curl);      // Clean up the curl handle
    }

    return 0;
}
