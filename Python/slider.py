import serial
# as 설정시 모듈명을 tk로 치환 한다
import tkinter as tk
# tkinter 내부의 ttk 위젯 모듈을 사용한다는 의미
from tkinter import ttk



#Tkinter GUI설정
window = tk.Tk()
window.title("RGB slider Controller")

#시리얼 연결
try:
    ser = serial.Serial("COM3", 115200)
except Exception as e:
    #print method는 앞에 f를 붙여야 {e} 에 대한 변수 값 내용이 나온다
    print(f"시리얼 포트 {e}에 연결할 수 없습니다.")
    ser = None

################################
#method 성성
################################
#데이터 전송
def send_data(channel, value):
    #함수에 내용이 없으면 pass 사용해야한다
    #pass
    if ser and ser.is_open:
        #빈공간은 0으로 채운다
        formatted_data=f"{channel}{int(value):03}\n"
        ser.write(formatted_data.encode('utf-8'))
        print(formatted_data)
        
    
#슬라이드 위젯 변경값 출력        
def on_slider_change(channel, slider):
    value = slider.get()
    #print(value)
    send_data(channel, value)
################################

# Red Slider
# command 시 파라미터 값을 변경이 불가능하다 
#r_slider = ttk.Scale(window, from_=0, to=999, command=r_slider_change())
#따라서, lambda 를 사용한다
r_slider = ttk.Scale(window, from_=0, to=999, length=600, command=lambda val:on_slider_change("R",r_slider))
g_slider = ttk.Scale(window, from_=0, to=999, length=600, command=lambda val:on_slider_change("G",g_slider))
b_slider = ttk.Scale(window, from_=0, to=999, length=600, command=lambda val:on_slider_change("B",b_slider))
r_slider.pack()
g_slider.pack()
b_slider.pack()

# 최종 인스턴스를 생성한다
window.mainloop()





