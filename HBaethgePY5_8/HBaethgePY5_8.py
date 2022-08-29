import tkinter as tk
import tkinter.font as tkfont

#create tkinter object
app = tk.Tk()

#set app title
app.winfo_toplevel().title("Python GUI Example")

#set object's size
app.geometry("500x500")

#create font style to use in app
fontStyle = tkfont.Font(family="The background is normal", size=20)

#create a label
labelExample = tk.Label(app, text="The background is normal", font=fontStyle)

def normal():
    #change label text
    labelExample.config(text = "The background is normal")
    #change background - using configure
    app.configure(bg='gray')

def bgRed():
    #change background for bgRed call - using configure
    app.configure(bg='red')
    #change label text
    labelExample.config(text = "The background is now red")
    #call normal reset method after 2 seconds
    app.after(2000, normal)

def bgGreen():
    #change background for bgGreen call - using 'bg'
    app['bg'] = 'green'
    #change label text
    labelExample.config(text = "The background is now green")
    #call normal reset method after 2 seconds
    app.after(2000, normal)    

def bgBlue():
    #change background for bgBlue call - using 'background'
    app['background'] = 'blue'
    #change label text
    labelExample.config(text = "The background is now blue")
    #call normal reset method after 2 seconds
    app.after(2000, normal)

#create a virtual image to be used for sizing the buttons in pixels instead of text units
pixelVirtual = tk.PhotoImage(width=1, height=1)

#put the label in the app using pack example (TOP, BOTTOM, LEFT, RIGHT)
labelExample.pack(side=tk.TOP)

#button 1
#button example - what window, button text, bacjground color, foreground color, use vertical image for sizing, width, height, compound="c" to show text
buttonExample1 = tk.Button(app, text="Red", bg="red", fg="white", image=pixelVirtual, width=100, height=50, compound="c", command = bgRed)
#use place to give the button a pixel location on screen
buttonExample1.place(x=175, y=100)

#button 2
buttonExample2 = tk.Button(app, text="Green", bg="green", fg="white", image=pixelVirtual, width=100, height=50, compound="c", command = bgGreen)
buttonExample2.place(x=175, y=200)

#button 3
buttonExample3 = tk.Button(app, text="Blue", bg="blue", fg="white", image=pixelVirtual, width=100, height=50, compound="c", command = bgBlue)
buttonExample3.place(x=175, y=300)

#minimal exit button and pack example (TOP, BOTTOM, LEFT, RIGHT)
buttonExample4 = tk.Button(app, text="EXIT", command = app.quit)
buttonExample4.pack(side=tk.BOTTOM)

app.mainloop()