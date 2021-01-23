/****************************************************************************
 *                                                                          *
 * QtVR--Physics-base inverse kinematics and inverse dynamics               *
 * Copyright (c) 2013 Joseph Cooper                                         *
 *                                                                          *
 * This software is provided 'as-is', without any express or implied        *
 * warranty. In no event will the authors be held liable for any damages    *
 * arising from the use of this software.                                   *
 *                                                                          *
 * Permission is granted to anyone to use this software for any purpose,    *
 * including commercial applications, and to alter it and redistribute it   *
 * freely, subject to the following restrictions:                           *
 *                                                                          *
 *  1. The origin of this software must not be misrepresented; you must not *
 *  claim that you wrote the original software. If you use this software    *
 *  in a product, an acknowledgment in the product documentation would be   *
 *  appreciated but is not required.                                        *
 *                                                                          *
 *  2. Altered source versions must be plainly marked as such, and must not *
 *  be misrepresented as being the original software.                       *
 *                                                                          *
 *  3. This notice may not be removed or altered from any source            *
 *  distribution.                                                           *
 ****************************************************************************/
#include <QApplication>
#include "mainwindow.h"
#include "testscript.h"
#include <iostream>
#include <QFile>
#include <QTextStream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    QString filename = "/Users/lijialiu/Documents/QtVR/data/optimization/parameters_opt.txt";

//    QFile file(filename);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        std::cout << "file error" << std::endl;
//        return 0;
//    }
//    QTextStream in(&file);

//    double p1, p2, p3, p4;
//    in >> p1;
//    in >> p2;
//    in >> p3;
//    in >> p4;

//   std::cout << p1 << std::endl;
//   std::cout << p2 << std::endl;
//   std::cout << p3 << std::endl;
//   std::cout << p4 << std::endl;

//   file.close();

//   w.updateParameters(p1, p2, p3, p4, 0.0);


//   w.experimentSlot();

//   int timer = 50;
//   while(timer > 0) {
//       w.updateLoop();
//       timer--;
//   }

//   w.experimentStopSlot();
//   w.loadMarkerFile("/Users/lijialiu/Documents/QtVR/data/motions/dmotions/02_04_jump.c3d", "/Users/lijialiu/Documents/QtVR/data/motions/dmotions/walk.c3d");


//    w.experimentSlot();

//    timer = 1500;
//    while(timer >= 0){
//            w.updateLoop();
//            timer--;
//    }
//    fopen("/Users/lijialiu/Documents/QtVR/data/optimization/done.txt","w");


    w.show();
    return a.exec();

}
