
# verbose sleep
def sleepv(seconds):
    import time
    import sys
    from math import floor, log10
    print('Wait ', end='')
    while seconds >= 0:
        print(f'{seconds}s', end='')
        if seconds > 0:        
            n = floor(log10(seconds))+1
            sys.stdout.flush()
            time.sleep(1.0)
            while n >= 0:
                print('\b \b', end='')
                n -= 1
        else:
            print('')
        seconds -= 1
