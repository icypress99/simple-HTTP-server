#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

#define PORT 8888

// Callback function to handle HTTP requests
static int answer_to_request(void *cls, struct MHD_Connection *connection,
                             const char *url, const char *method,
                             const char *version, const char *upload_data,
                             size_t *upload_data_size, void **con_cls) {

    const char *response_str = "Hello, World!";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(response_str),
                                               (void*)response_str,
                                               MHD_RESPMEM_PERSISTENT);
    if (!response) {
        return MHD_NO;
    }

    // Add a content-type header for the response
    MHD_add_response_header(response, "Content-Type", "text/plain");

    // Send the response to the client
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);

    // Clean up the response object
    MHD_destroy_response(response);

    return ret;
}

struct MHD_Daemon *start(){
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, PORT, NULL, NULL,
                              &answer_to_request, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon) {
        fprintf(stderr, "Failed to start HTTP server\n");
    }else{
        printf("Server is running on http://localhost:%d\n", PORT);
    }

    return daemon;
}

int main() {

    struct MHD_Daemon *daemon = start();

    printf("Press Enter to stop the server.\n");

    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}
