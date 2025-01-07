from __future__ import print_function

import logging

import grpc
import hello_pb2
import hello_pb2_grpc

def run():
    print("Hello Prakarn J.")
    with grpc.insecure_channel("localhost:9999") as channel:
        stub = hello_pb2_grpc.ProcessingServicesStub(channel)
        response = stub.computeSum(hello_pb2.Point3(x=3, y=4, z=5))
    print("response received: " + f'{response.value}')

if __name__ == "__main__":
    logging.basicConfig()
    run()
