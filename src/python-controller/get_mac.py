import getmac
import hashlib

def get_mac():
    mac = getmac.get_mac_address(interface='eth0')
    if mac is None:
        mac = getmac.get_mac_address()
    return mac.lower()

def get_mac_hash():
    mac = get_mac()
    h = hashlib.sha256(mac.encode()).hexdigest()
    return str(h)

if __name__ == '__main__':
    #print(get_mac())
    print(get_mac_hash())
