import getmac

def get_mac():
    mac = getmac.get_mac_address(interface='eth0')
    if mac is None:
        mac = getmac.get_mac_address()
    return mac.lower()

if __name__ == '__main__':
    print(mac)
