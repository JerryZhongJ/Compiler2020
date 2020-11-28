# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'MainWindow.ui'
#
# Created: Fri Feb 24 09:42:37 2012
#      by: PyQt4 UI code generator 4.9.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

# try:
#     _fromUtf8 = QString.fromUtf8
# except AttributeError:
#     _fromUtf8 = lambda s: s

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 600)
        sizePolicy = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MainWindow.sizePolicy().hasHeightForWidth())
        MainWindow.setSizePolicy(sizePolicy)
        MainWindow.setMinimumSize(QSize(800, 600))
        MainWindow.setMaximumSize(QSize(800, 600))
        icon = QIcon()
        icon.addPixmap(QPixmap(":/icon.png"), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.layoutWidget = QWidget(self.centralwidget)
        self.layoutWidget.setGeometry(QRect(20, 10, 761, 490))
        self.layoutWidget.setObjectName("layoutWidget")
        self.horizontalLayout = QHBoxLayout(self.layoutWidget)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.label = QLabel(self.layoutWidget)
        font = QFont()
        font.setFamily("Verdana")
        font.setBold(True)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.verticalLayout.addWidget(self.label)
        self.codeList = QListWidget(self.layoutWidget)
        self.codeList.setEnabled(True)
        font = QFont()
        font.setFamily("Arial")
        self.codeList.setFont(font)
        self.codeList.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.codeList.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.codeList.setObjectName("codeList")
        self.verticalLayout.addWidget(self.codeList)
        self.horizontalLayout.addLayout(self.verticalLayout)
        spacerItem = QSpacerItem(40, 20, QSizePolicy.Preferred, QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.label_2 = QLabel(self.layoutWidget)
        font = QFont()
        font.setFamily("Verdana")
        font.setBold(True)
        font.setWeight(75)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.verticalLayout_2.addWidget(self.label_2)
        self.watchTable = QTableWidget(self.layoutWidget)
        font = QFont()
        font.setFamily("Arial")
        self.watchTable.setFont(font)
        self.watchTable.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.watchTable.setSelectionMode(QAbstractItemView.SingleSelection)
        self.watchTable.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.watchTable.setHorizontalScrollMode(QAbstractItemView.ScrollPerPixel)
        self.watchTable.setObjectName("watchTable")
        self.watchTable.setColumnCount(3)
        self.watchTable.setRowCount(0)
        item = QTableWidgetItem()
        self.watchTable.setHorizontalHeaderItem(0, item)
        item = QTableWidgetItem()
        self.watchTable.setHorizontalHeaderItem(1, item)
        item = QTableWidgetItem()
        self.watchTable.setHorizontalHeaderItem(2, item)
        self.verticalLayout_2.addWidget(self.watchTable)
        spacerItem1 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Preferred)
        self.verticalLayout_2.addItem(spacerItem1)
        self.label_3 = QLabel(self.layoutWidget)
        font = QFont()
        font.setFamily("Verdana")
        font.setBold(True)
        font.setWeight(75)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.verticalLayout_2.addWidget(self.label_3)
        self.console = QTextEdit(self.layoutWidget)
        font = QFont()
        font.setFamily("Serif")
        self.console.setFont(font)
        self.console.setReadOnly(True)
        self.console.setObjectName("console")
        self.verticalLayout_2.addWidget(self.console)
        self.horizontalLayout.addLayout(self.verticalLayout_2)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setGeometry(QRect(0, 0, 800, 25))
        self.menubar.setObjectName("menubar")
        self.menuFile = QMenu(self.menubar)
        self.menuFile.setObjectName("menuFile")
        self.menuRun = QMenu(self.menubar)
        self.menuRun.setObjectName("menuRun")
        self.menuAbout = QMenu(self.menubar)
        self.menuAbout.setObjectName("menuAbout")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.toolBar = QToolBar(MainWindow)
        self.toolBar.setObjectName("toolBar")
        MainWindow.addToolBar(Qt.TopToolBarArea, self.toolBar)
        self.action_Open = QAction(MainWindow)
        icon1 = QIcon()
        icon1.addPixmap(QPixmap(":/filenew.png"), QIcon.Normal, QIcon.Off)
        self.action_Open.setIcon(icon1)
        self.action_Open.setObjectName("action_Open")
        self.actionQuit = QAction(MainWindow)
        icon2 = QIcon()
        icon2.addPixmap(QPixmap(":/filequit.png"), QIcon.Normal, QIcon.Off)
        self.actionQuit.setIcon(icon2)
        self.actionQuit.setObjectName("actionQuit")
        self.actionRun = QAction(MainWindow)
        self.actionRun.setEnabled(True)
        icon3 = QIcon()
        icon3.addPixmap(QPixmap(":/run.png"), QIcon.Normal, QIcon.Off)
        self.actionRun.setIcon(icon3)
        self.actionRun.setObjectName("actionRun")
        self.actionStop = QAction(MainWindow)
        self.actionStop.setEnabled(True)
        icon4 = QIcon()
        icon4.addPixmap(QPixmap(":/stop.png"), QIcon.Normal, QIcon.Off)
        self.actionStop.setIcon(icon4)
        self.actionStop.setObjectName("actionStop")
        self.actionStep = QAction(MainWindow)
        self.actionStep.setEnabled(True)
        icon5 = QIcon()
        icon5.addPixmap(QPixmap(":/step.png"), QIcon.Normal, QIcon.Off)
        self.actionStep.setIcon(icon5)
        self.actionStep.setObjectName("actionStep")
        self.actionAbout = QAction(MainWindow)
        self.actionAbout.setIcon(icon)
        self.actionAbout.setObjectName("actionAbout")
        self.menuFile.addAction(self.action_Open)
        self.menuFile.addSeparator()
        self.menuFile.addAction(self.actionQuit)
        self.menuRun.addAction(self.actionRun)
        self.menuRun.addAction(self.actionStop)
        self.menuRun.addAction(self.actionStep)
        self.menuAbout.addAction(self.actionAbout)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuRun.menuAction())
        self.menubar.addAction(self.menuAbout.menuAction())
        self.toolBar.addAction(self.action_Open)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.actionRun)
        self.toolBar.addAction(self.actionStep)
        self.toolBar.addAction(self.actionStop)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.actionQuit)

        self.retranslateUi(MainWindow)
        QMetaObject.connectSlotsByName(MainWindow)
        MainWindow.setTabOrder(self.codeList, self.watchTable)
        MainWindow.setTabOrder(self.watchTable, self.console)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QApplication.translate("MainWindow", "IR Simulator", None))
        self.label.setText(QApplication.translate("MainWindow", "Code", None))
        self.label_2.setText(QApplication.translate("MainWindow", "Watch", None))
        item = self.watchTable.horizontalHeaderItem(0)
        item.setText(QApplication.translate("MainWindow", "Variable", None))
        item = self.watchTable.horizontalHeaderItem(1)
        item.setText(QApplication.translate("MainWindow", "Address", None))
        item = self.watchTable.horizontalHeaderItem(2)
        item.setText(QApplication.translate("MainWindow", "Value", None))
        self.label_3.setText(QApplication.translate("MainWindow", "Console", None))
        self.menuFile.setTitle(QApplication.translate("MainWindow", "File", None))
        self.menuRun.setTitle(QApplication.translate("MainWindow", "Run", None))
        self.menuAbout.setTitle(QApplication.translate("MainWindow", "About", None))
        self.toolBar.setWindowTitle(QApplication.translate("MainWindow", "toolBar", None))
        self.action_Open.setText(QApplication.translate("MainWindow", "&Open...", None))
        self.action_Open.setStatusTip(QApplication.translate("MainWindow", "Open an existing IR file", None))
        self.action_Open.setWhatsThis(QApplication.translate("MainWindow", "Open", None))
        self.action_Open.setShortcut(QApplication.translate("MainWindow", "Ctrl+O", None))
        self.actionQuit.setText(QApplication.translate("MainWindow", "&Quit", None))
        self.actionQuit.setStatusTip(QApplication.translate("MainWindow", "Quit the application", None))
        self.actionQuit.setShortcut(QApplication.translate("MainWindow", "Esc", None))
        self.actionRun.setText(QApplication.translate("MainWindow", "&Run", None))
        self.actionRun.setStatusTip(QApplication.translate("MainWindow", "Run the code", None))
        self.actionRun.setShortcut(QApplication.translate("MainWindow", "F5", None))
        self.actionStop.setText(QApplication.translate("MainWindow", "St&op", None))
        self.actionStop.setStatusTip(QApplication.translate("MainWindow", "Stop the current running process", None))
        self.actionStop.setShortcut(QApplication.translate("MainWindow", "F4", None))
        self.actionStep.setText(QApplication.translate("MainWindow", "St&ep...", None))
        self.actionStep.setStatusTip(QApplication.translate("MainWindow", "Run the code step by step", None))
        self.actionStep.setShortcut(QApplication.translate("MainWindow", "F8", None))
        self.actionAbout.setText(QApplication.translate("MainWindow", "&About...", None))
        self.actionAbout.setStatusTip(QApplication.translate("MainWindow", "About this application", None))

import resources_rc
