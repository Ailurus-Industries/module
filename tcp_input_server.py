import XInput
from typing import List
import socket
import time
import struct
import multiprocessing

controller_statuses: List[int] = []

while True not in controller_statuses:
    controller_statuses = XInput.get_connected()
    if True not in controller_statuses:
        print("No controllers available! Press enter to try again. ", end="")
        input()

available_ports = [i for i, x in enumerate(controller_statuses) if x]
port = available_ports[0]

print(f"Available Controllers: {available_ports}")
print(f"Controller Port {port} selected.")

from flask import Flask, jsonify

app = Flask(__name__)

# Define the pressed variable
pressed = False

@app.route('/status', methods=['GET'])
def get_status():

    state = XInput.get_state(port)

    A_button_pressed = state.Gamepad.wButtons & 0x1000

    return str(A_button_pressed)

if __name__ == '__main__':
    app.run(host="0.0.0.0", debug=True)

multiprocessing.pool()
