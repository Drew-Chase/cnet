//
// Created by drew.chase on 4/9/2024.
//

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "http_message.h"

namespace cnet {

class http_client {

public:
    void make_request(http_message& message);


};

} // cnet

#endif //HTTP_CLIENT_H
