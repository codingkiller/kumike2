/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <bb/cascades/Application>

#include <QLocale>
#include <QTranslator>
#include "applicationui.hpp"
#include "network.hpp"
#include <Qt/qdeclarativedebug.h>
#include <bb/cascades/QmlDocument>

using namespace bb::cascades;

void myMessageOutput(QtMsgType type, const char* msg) {
 std::fprintf(stdout, "%s\n", msg);
 std::fflush(stdout);
}


Q_DECL_EXPORT int main(int argc, char **argv)
{
	qmlRegisterType<NetworkBus>("NetworkBus", 1, 0, "NetworkBus");
	qmlRegisterType<station>("station", 1, 0, "station");
	qmlRegisterType<station>("BusGps", 1, 0, "BusGps");
    Application app(argc, argv);
    qInstallMsgHandler(myMessageOutput);


    // Create the Application UI object, this is where the main.qml file
    // is loaded and the application scene is set.
    new ApplicationUI(&app);

    // Enter the application main event loop.
    return Application::exec();
}
