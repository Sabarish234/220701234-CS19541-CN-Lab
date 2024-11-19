import socket
def recvr1():
    port=12345
    host='127.0.0.1'
    with socket.socket(socket.AF_INET,socket.SOCK_DGRAM) as s:
        s.bind((host,port))
        while(True):
            d,add=s.recvfrom(1024)
            print("Client",{d.decode()})
            a=input("Enter Reply ")
            s.sendto(a.encode(),add)
            if(a=="end"):
                break
                exit
recvr1()        
