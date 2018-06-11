from pyaudio import PyAudio,paInt16
import numpy as np
import threading
import time
import Queue
import matplotlib.pyplot as plt
import matplotlib.animation as animation

chunk = 1024
sampling_rate = 8000

time_domain_raw_q_buffer=Queue.Queue()

time_domain_array_buffer=np.array([],dtype=np.short)

plot_width = chunk * 20
plot_height = 40000
plot_shift = 0
anim_speed = 10

input_audio = PyAudio()
output_audio = PyAudio()

input_stream = input_audio.open(format = paInt16,channels = 1,rate=sampling_rate,input = True,frames_per_buffer = chunk)
output_stream = output_audio.open(format = paInt16,channels = 1,rate = sampling_rate,output = True)

def input_thread():
    while True:
        global time_domain_array_buffer
        stream_data=input_stream.read(chunk)
        time_domain_raw_q_buffer.put(stream_data)
        time_domain_array_buffer = np.append(time_domain_array_buffer,np.fromstring(stream_data,dtype = np.short))
        diff = len(time_domain_array_buffer)-plot_shift-plot_width
        if diff > 0:
            global anim_speed
            anim_speed = int(diff/10)
        #else:
            #anim_speed = int(anim_speed*9/10)

        print "diff     " + str(diff)
        print "plot_width        " + str(plot_width)
        print "anim_speed                " + str(anim_speed)
        print "len of Buffer                    " + str(len(time_domain_array_buffer))

def output_thread():
    global time_domain_array_buffer
    while True:
        string_audio_data = time_domain_raw_q_buffer.get()
        output_stream.write(string_audio_data)

        time_domain_array_buffer = np.append(time_domain_array_buffer,np.fromstring(string_audio_data,dtype = np.short))
        
        diff = len(time_domain_array_buffer)-plot_shift-plot_width
        if diff > 0:
            global anim_speed
            anim_speed = int(diff/30)
        #else:
            #anim_speed = int(anim_speed*9/10)

        print "diff     " + str(diff)
        print "plot_width        " + str(plot_width)
        print "anim_speed                " + str(anim_speed)
        print "len of Buffer                    " + str(len(time_domain_array_buffer))

def update(data):
    line_time_domain_from_real.set_ydata(data)
    fft_data=np.fft.fft(data[-chunk:])/chunk
    line_freq_domain_from_time.set_ydata(fft_data)
    return line_time_domain_from_real,line_freq_domain_from_time

def data_gen():
    if len(time_domain_array_buffer)<chunk:
        yield np.zeros((1,chunk),dtype=np.short)
    else:
        global plot_shift
        plot_shift = plot_shift + anim_speed
        yield time_domain_array_buffer[plot_shift :plot_shift + plot_width]

input_thread=threading.Thread(target = input_thread)
output_thread=threading.Thread(target = output_thread)

fig=plt.figure()
axes_time_domain_from_real=fig.add_subplot(311)
axes_freq_domain_from_time=fig.add_subplot(312)
axes_time_domain_from_freq=fig.add_subplot(313)
axes_time_domain_from_real.set_ylim(-plot_height,plot_height)
axes_freq_domain_from_time.set_ylim(-500,500)
line_time_domain_from_real,=axes_time_domain_from_real.plot(np.random.rand(plot_width))
line_freq_domain_from_time,=axes_freq_domain_from_time.plot(np.random.rand(chunk))

input_thread.start()
time.sleep(0.5)
output_thread.start()
time.sleep(0.2)
ani=animation.FuncAnimation(fig,update,data_gen,interval = 50)
plt.show()
