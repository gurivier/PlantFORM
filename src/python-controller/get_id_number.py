from get_mac import get_mac

def get_id_number():
    id_numbers = {
        'dc:a6:32:67:ad:6c': 1,
        'e4:5f:01:f5:fb:77': 2,
        'dc:a6:32:c9:5f:ed': 3,
        'dc:a6:32:c9:22:13': 4,
        'e4:5f:01:5c:28:5a': 5
    }
    mac = get_mac()
    return id_numbers[mac]

if __name__ == '__main__':
    print(get_id_number())
