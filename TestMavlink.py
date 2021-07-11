import serial
import glob
import numpy as np
from sys import platform


class Serial_ports(object):

    def __init__(self):
        self.ports_list = []
        self.serial_port = None
        self.get_ports()

    def __search_port(self):
        """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
        """
        if platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif platform.startswith('linux') or sys.platform.startswith('cygwin'):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        return result

    def get_ports(self):
        self.ports_list = self.__search_port()

    def open_port(self, port, baud_rate, timeout):
        self.serial_port = serial.Serial(port, baud_rate, timeout=timeout)


def twos_comp(val, bits):
    """compute the 2's complement of int value val"""
    if (val & (1 << (bits - 1))) != 0:  # if sign bit is set e.g., 8bit: 128-255
        val = val - (1 << bits)        # compute negative value
    return val                         # return positive value as is


if __name__ == '__main__':
    serials = Serial_ports()
    if('/dev/ttyUSB0' in serials.ports_list):
        serials.open_port('/dev/ttyUSB0', 115200, 0xff)
        while(1):
            data = serials.serial_port.read(12)
            hdata = []
            hdata.append(twos_comp((data[0] << 8)+data[1], 16))
            hdata.append(twos_comp((data[2] << 8)+data[3], 16))
            hdata.append(twos_comp((data[4] << 8)+data[5], 16))
            hdata.append(twos_comp((data[6] << 8)+data[7], 16))
            hdata.append(twos_comp((data[8] << 8)+data[9], 16))
            hdata.append(twos_comp((data[10] << 8)+data[11], 16))
            angle = np.arctan2(hdata[1], hdata[0]) * (180/np.pi) + 180

            print(angle,hdata)
