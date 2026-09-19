
def get_access_point_ip():
    import os
    routes = os.popen('netstat -r -n | tail -n +3').readlines()
    gateways = [ ips.split()[1] for ips in routes ]
    gateway = ''
    for ip in gateways:
        if ip[0:3] == '192':
            gateway = ip
    return gateway
            
if __name__ == '__main__':
    import sys
    ap_ip = get_access_point_ip()
    print(f'AP: "{ap_ip}"')
    sys.exit(0)



