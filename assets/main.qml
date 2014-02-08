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

import bb.cascades 1.0
import NetworkBus 1.0

Page {
    titleBar: TitleBar {
        title: qsTr("酷米客公交 ")
    }
    Container {
        
        DropDown {
            id: cityDropDown
            title: "城市"
            Option {
                text: "深圳"
                selected: true
                description: "广东省深圳市，区号0755"
                value: "860515"
            }
            
            Option {
                text: "北京"
                description: "北京市，区号010"
                value: "860201"
            }
            
            Option {
                text: "西安"
                description: "陕西省西安市，区号0917"
                value: "862307"
            }
            onSelectedIndexChanged: {
                networkBus.changeCity(cityDropDown.selectedValue)
            }
        }
        TextField {
            id: line_name
            text: "M264"
            textStyle.base: SystemDefaults.TextStyles.BigText
        }
        Button {
        	id: button
        	text: "push me"
        	onClicked: {
                networkBus.get_lines_by_city(cityDropDown.selectedValue,line_name.text)
         }
        }
        TextArea {
        	id: testArea
            text: networkBus.buslineText
        }
        Label {
            id: stopInfo
            text: "起始站点"
        }
        Label {
            id: timeInfo
            text: "起止时间"
        }
        attachedObjects: [
            NetworkBus {
                id: networkBus
            }
        ]
    }
}
