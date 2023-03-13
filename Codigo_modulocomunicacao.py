import http.client
import urllib.parse
import serial
import numpy as np
# Acima temos as importações de de bibliotecas necessarias para o funcionamento do programa 


s=serial.Serial('/dev/ttyUSB0', 9600)  # linha responsavel  pela conexão do raspberry com o arduino via APC220
s.bytesize=serial.EIGHTBITS # apartir desta linha estão sendo definidos os parametros da comunicação APC220
s.parity=serial.PARITY_NONE
s.stopbits=serial.STOPBITS_ONE
s.timeout=0
s.xonxoff=False
s.rtscts=False
s.dsrdtr=False
s.setRTS(0)



def thinkspeak(): # função responsavel por enviar os dados recebidos para o thinkspeak
    while True:   
        params = urllib.parse.urlencode({'field1': list[0],'field2': list[1],'field3': list[2], 'key':key }) 
        headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
        conn = http.client.HTTPConnection("api.thingspeak.com:80")
        try:
            conn.request("POST", "/update", params, headers)
            response = conn.getresponse()
            print (response.status, response.reason)
            data = response.read()
            conn.close()
        except:
            print ("connection failed")
        break
        


while (True):
    list=['','','','']          #lista responsavel por receber os dados e organizar para ser enviado ao thinkspeak 
    valor_recebido=s.readline()  #recebe os valores enviados pelo arduino
    print(valor_recebido)
    a=str(valor_recebido)       #transforma os valores recebidos em uma string
    data=a.split("#")           #divide a string a partir do marcador(#)
    print(data)
    if len(data)<4:             #se apos a divisao a string for menor que 4 parcelas se descarta a string atual
        x=0
    else:
        del data[3]             #se apaga um parcela sem utilidade da string para melhor organizar 
        print(a)
        print(data)
        c=data.pop(1)           #verificação do marcador (a,b,c ou d) para definir qual o sensor que enviou a medição
        b=data.pop(1)           #verificação do valor recebido da medição
        b=float(b)              #string da medição transformada em float
        if c=="a":
            list[0]=b           #posicionamento do valor de medição na lista 
        elif c=="b":
            list[1]=b           #posicionamento do valor de medição na lista 
        elif c=="c":
            list[2]=b           #posicionamento do valor de medição na lista 
        print(b)
        if (valor_recebido.decode("utf-8") != "300"):       #usado para não haver erros na string
            
            
            print(list)
            print(valor_recebido)
            key = "1VLJHYRBSQMWWECD"                # chave utilizada para escrever os dados no thinkspeak
            thinkspeak()                            #chamada da função
            


