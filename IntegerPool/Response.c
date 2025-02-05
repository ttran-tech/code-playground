#include "Response.h"

Response generate_response(pid_t client_id, int value)
{
    Response response;
    response.client_id = client_id;
    response.value = value;
    return response;
}