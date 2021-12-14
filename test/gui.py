#!/usr/bin/python3.6
import matplotlib
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon

matplotlib.use('Qt5Agg')

class Window(QWidget):
    def __init__(self,parent=None):
        super(Window,self).__init__(parent)
        self.initUI()
    
    def initUI(self):

        grid=QGridLayout() 
        self.resize(1000,600)
        self.move(1000,1000)
        self.setWindowTitle('gui')

        lb=QLabel(self) 
        lb.move(10,5)
        lb.setText('abc')
        
        table=QTableWidget(10,3,self);
        table.setParent(self)
        table.resize(300,300)
        table.move(10,20) 
        
        button1=QPushButton('generat',self);
        button2=QPushButton('reset',self);
        button3=QPushButton('none',self);
        
        button1.resize(300,30)
        button2.resize(300,30)
        button3.resize(300,30)
       

        button1.move(10,330);
        button2.move(10,370);
        button3.move(10,410);

        #グラフ生成
        figure=Figure(figsize=(5,10))
        #キャンバス生成
        fcanvas=FigureCanvas(figure)

        fcanvas.axes=figure.add_subplot(111)
        fcanvas.axes.plot([1,2,3],[2,3,4])
        fcanvas.setParent(self)

        fcanvas.resize(600,420)
        fcanvas.move(350,10)


if __name__=='__main__':
    app=QApplication(sys.argv)
    window=Window() 
    window.show()
    sys.exit(app.exec_())

        
