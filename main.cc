#include <array>
#include <iostream>
#include <vector>

#include "zmq.hpp"

#include "image_helper.h"
#include "network_helper.h"
#include "serialization.h"
#include "utility.h"

namespace {

enum class RequestType : int32_t {
  kIpRequest = 700,
  kPingRequest,
  kImageRequest,

};
struct Request {
  RequestType type;
  std::vector<uint8_t> data;
};

enum class ResponseType : int32_t {
  kSuccess = 200,
  kBadRequest = 400,
};

Request ConstructRequestFromPackedData(zmq::socket_t& socket) {
  zmq::message_t message;
  socket.recv(&message, ZMQ_SNDMORE);

  if (message.size() != sizeof(RequestType))
    return {};

  Request request;

  uint32_t request_type =
      serialization::ToUint32(reinterpret_cast<uint8_t*>(message.data()));
  request.type = static_cast<RequestType>(request_type);

  while (message.more()) {
    socket.recv(&message, ZMQ_SNDMORE);

    auto begin = reinterpret_cast<uint8_t*>(message.data());
    auto end = begin + message.size();

    request.data.reserve(request.data.size() + message.size());
    std::copy(begin, end, std::back_inserter(request.data));
  }

  return request;
}

template <typename Container>
void SendMultipartMessage(zmq::socket_t& socket,
                          ResponseType type,
                          const Container& data) {
  std::vector<uint8_t> serialized =
      serialization::FromUint32(static_cast<uint32_t>(type));
  socket.send(&serialized[0], serialized.size(), ZMQ_SNDMORE);
  socket.send(&data[0], data.size());
}

}  // namespace

int main(int argc, char** argv) {
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REP);
  socket.bind("tcp://*:5555");

  Request request;
  while (true) {
    request = ConstructRequestFromPackedData(socket);
    switch (request.type) {
      case RequestType::kIpRequest: {
        std::vector<std::string> ip_addresses =
            network_helper::GetActiveAdaptersIPs();
        SendMultipartMessage(socket, ResponseType::kSuccess,
                             utility::JoinString(ip_addresses, ';'));
        break;
      }
      case RequestType::kPingRequest:
        SendMultipartMessage(socket, ResponseType::kSuccess,
                             std::string("pong"));
        break;

      case RequestType::kImageRequest: {
        image_helper::Image image =
            image_helper::DecodeJpegFromBuffer(request.data);
        if (image.IsEmpty()) {
          SendMultipartMessage(socket, ResponseType::kBadRequest,
                               std::string("Bad data"));
        } else {
          uint32_t average = image_helper::GetAveragePixelValue(image);
          std::vector<uint8_t> average_serialized =
              serialization::FromUint32(average);

          SendMultipartMessage(socket, ResponseType::kSuccess,
                               average_serialized);
        }
        break;
      }
      default:
        SendMultipartMessage(socket, ResponseType::kBadRequest,
                             std::string("Unknown command"));
        break;
    }
  }

  return 0;
}