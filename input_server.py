import XInput
from typing import List
import socket
import time
import struct
import multiprocessing


def send_data(port, addr):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    idx = 0
    while True:
        print(addr)
        state = XInput.get_state(port)

        buttons = state.Gamepad.wButtons
        lTrigger = state.Gamepad.bLeftTrigger
        rTrigger = state.Gamepad.bRightTrigger
        # 10% deadband (32767 * 0.1)
        joyLX = (
            state.Gamepad.sThumbLX if abs(state.Gamepad.sThumbLX) > 3300 else 0
        )
        joyLY = (
            state.Gamepad.sThumbLY if abs(state.Gamepad.sThumbLY) > 3300 else 0
        )
        joyRX = (
            state.Gamepad.sThumbRX if abs(state.Gamepad.sThumbRX) > 3300 else 0
        )
        joyRY = (
            state.Gamepad.sThumbRY if abs(state.Gamepad.sThumbRY) > 3300 else 0
        )

        data = struct.pack(
            "<bbbIBHBBhhhh",
            0x43, 0x4f, 0x4e, idx, port,
            buttons, lTrigger, rTrigger,
            joyLX, joyLY, joyRX, joyRY
        )
        # print(f"{data.hex()}")
        idx = (idx + 1) % 2147483647
        time.sleep(0.1)
        sock.sendto(data, addr)


def main():
    controller_statuses: List[int] = []

    while True not in controller_statuses:
        controller_statuses = XInput.get_connected()
        if True not in controller_statuses:
            print("No controllers available! Press enter to try again. ",
                  end="")
            input()

    available_ports = [i for i, x in enumerate(controller_statuses) if x]
    port = available_ports[0]

    print(f"Available Controllers: {available_ports}")
    print(f"Controller Port {port} selected.")

    ADDR1 = ("10.42.0.14", 5000)
    # CLAW = ("10.42.0.140", 5000)
    # ADDR2 = ("10.42.0.249", 5000)
    ADDR3 = ("10.42.0.74", 5000)

    p = multiprocessing.Process(
        target=send_data, args=(available_ports[0], ADDR1)
    )
    p.start()
    p2 = multiprocessing.Process(
        target=send_data, args=(available_ports[1], ADDR3)
    )
    p2.start()

    # p3 = multiprocessing.Process(
    #     target=send_data, args=(available_ports[0], CLAW)
    # )
    # p3.start()

    # p4 = multiprocessing.Process(
    #     target=send_data, args=(available_ports[0], ADDR2)
    # )
    # p4.start()

    p.join()
    p2.join()
    # p3.join()
    # p4.join()


# {
#     "DPAD_UP": bool(wButtons & 0x0001),
#     "DPAD_DOWN": bool(wButtons & 0x0002),
#     "DPAD_LEFT": bool(wButtons & 0x0004),
#     "DPAD_RIGHT": bool(wButtons & 0x0008),
#     "START": bool(wButtons & 0x0010),
#     "BACK": bool(wButtons & 0x0020),
#     "LEFT_THUMB": bool(wButtons & 0x0040),
#     "RIGHT_THUMB": bool(wButtons & 0x0080),
#     "LEFT_SHOULDER": bool(wButtons & 0x0100),
#     "RIGHT_SHOULDER": bool(wButtons & 0x0200),
#     "A": bool(wButtons & 0x1000),
#     "B": bool(wButtons & 0x2000),
#     "X": bool(wButtons & 0x4000),
#     "Y": bool(wButtons & 0x8000),
# }
# print(f"{state.Gamepad.wButtons:>016b}")
# Trigger values max at 255
# print(f"{state.Gamepad.bLeftTrigger}")
# print(f"{state.Gamepad.bRightTrigger}")
# # Joystick values max at 32767
# print(f"{state.Gamepad.sThumbLX}")
# print(f"{state.Gamepad.sThumbLY}")
# print(f"{state.Gamepad.sThumbRX}")
# print(f"{state.Gamepad.sThumbRY}")
# button_values = state.Gamepad.wButtons
# button_values = XInput.get_button_values(state)
# trigger_values = XInput.get_trigger_values(state)  # (lt, rt)
# thumb_values = XInput.get_thumb_values(state)  # (lx, ly), (rx, ry)
# print(button_values)
# print(trigger_values)
# print(thumb_values)

if __name__ == "__main__":
    multiprocessing.freeze_support()
    main()
