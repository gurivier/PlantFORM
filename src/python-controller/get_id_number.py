from get_mac import get_mac_hash

def get_id_number():
    id_numbers = {
        'fbff9546437557f7803f10cf45f79a1df9bebc8c40ce3c67dbbe0fb6012a1d03': 1,
        '08ec775da840bc108b0d257467452b57710cb61fd4b2a35ca8d4bace3938a2bb': 2,
        '0c7c77376291ede9bc1005a7fabbdf6e73e969af514b97894ef6195098c17695': 3,
        '35659febd5e10a7c5fee2a8bdf1c05dd8eafb90479f416b9a6291650d0106078': 4,
        '283c995a8e4527e646edb942f63f2dede29b1d4d0952c4d0dd200131e16db441': 5
    }
    mac_hash = get_mac_hash()
    return id_numbers[mac_hash]

if __name__ == '__main__':
    print(get_id_number())
