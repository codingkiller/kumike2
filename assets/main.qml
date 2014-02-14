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
import bb.system 1.0
import bb.data 1.0
import station 1.0
//import BusGps 1.0
NavigationPane {
    id: navigationPane

Page {
    
    titleBar: TitleBar {
        id: titleBar
    //    title: qsTr("ku mi x")
        kind: TitleBarKind.FreeForm
        kindProperties: FreeFormTitleBarKindProperties {
            Container {
                id: firstContainer
           //     background: Color.Red
           //     maxHeight: 500
                layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
                topPadding: 20
                verticalAlignment: VerticalAlignment.Bottom
                horizontalAlignment: HorizontalAlignment.Center
                Label {
                    text: qsTr("酷米客公交 ")
                    textStyle {
                        color: Color.White
                        fontSize: FontSize.XLarge
                        textAlign: TextAlign.Right
                    }
                    maxWidth: 400
                    horizontalAlignment: HorizontalAlignment.Right
                    layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                }
                Label {
                    id: city_name
                    text: "深圳"
                    
                    textStyle{
                        color: Color.White
                    }
                    verticalAlignment:VerticalAlignment.Center
                //    topPadding: 50
                //    bottomPadding: 0
                 //   rightPadding: 0
                    maxWidth: 74
                    attachedObjects: [
                        SystemListDialog{
                            property bool created: false
                            property int  value: 860515
                            id:listDialog
                            title:"选择城市"
                            selectionMode: ListSelectionMode.Single
                            confirmButton.label: "确定"
                            cancelButton.label: "取消"
                         //   includeRememberMe: true
                         //   rememberMeChecked: true
                            
                            onFinished: {
                                if(listDialog.result == SystemUiResult.CancelButtonSelection){
                                    return;
                                }
                                if(selectedIndices.length > 0){
                                    var indexpath = selectedIndices[0];
                                    console.log("indexpath : "+ indexpath);
                                    if(indexpath == 0){//beijing
                                        indexpath = 860201;
                                        city_name.text = "北京"
                                    }else if(indexpath == 1){
                                        indexpath = 860515;
                                        city_name.text = "深圳"
                                    }else{
                                        city_name.text = "西安"
                                        indexpath = 862307;
                                    }
                                    listDialog.value = indexpath;
                                    console.log("===="+listDialog.value);
                                }
                            }
                        }
                    ]
                    onTouch: {
                            listDialog.clearList();
                            listDialog.appendItem("北京 ",true ,listDialog.value == 860201  );
                            listDialog.appendItem("深圳",true ,listDialog.value == 860515  );
                            listDialog.appendItem("西安",true,listDialog.value == 862307);
                        listDialog.show();
                    }
                }
                ImageView {
                    imageSource: "asset:///images/ic_location.png"
                    horizontalAlignment: HorizontalAlignment.Left
                    onTouch: {
                        listDialog.clearList();
                        listDialog.appendItem("北京 ",true ,listDialog.value == 860201  );
                        listDialog.appendItem("深圳",true ,listDialog.value == 860515  );
                        listDialog.appendItem("西安",true,listDialog.value == 862307);
                        listDialog.show();
                    }
                }
            }
        }
    }
    
    Container {
        id: secondContainer
        leftPadding: 50
        rightPadding: 50
        preferredWidth: 668
        horizontalAlignment: HorizontalAlignment.Center

        Container {
         topPadding: 100
        TextField {
            id: line_name
            preferredWidth: 440
            textStyle.fontSize: FontSize.XXLarge
            hintText: qsTr("请输入实时公交线路 ")
            text: qsTr("M264")
            }
        Button {
            text: qsTr("查询")
            imageSource: "asset:///images/ic_search.png"
            maxWidth: 200
            onClicked: {
                networkBus.get_lines_by_city(listDialog.value,line_name.text)
                var page = pageDefinition.createObject()
                navigationPane.push(page)
            }
            
        }
       /* Button {
        	id: button
        	text: "查询"
        	maxWidth: 200
        	onClicked: {
                networkBus.get_lines_by_city(listDialog.value,line_name.text)
                var page = pageDefinition.createObject()
                navigationPane.push(page)
         }
        }*/
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight
        }
    }
        
    
    Container {
        topPadding: 100
        Label {
            text: "常用线路"
            textStyle{
                fontWeight: FontWeight.W100
                fontSize: FontSize.Large
            }
        }
        Container {
            background: Color.Blue
            preferredHeight: 2
            preferredWidth: 768
        }
        ListView {
            property NetworkBus networkBus : networkBus
            id: localDataList
            visible: !networkBus.process
            dataModel: networkBus.localDataModel
            layout: StackListLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            topPadding: 0
            listItemComponents: [
                ListItemComponent {
                    Container {
                        id: rootItem
                        layout: StackLayout {
                            orientation: LayoutOrientation.TopToBottom
                        }
                        minWidth: 120
                        Container {
                            minWidth: 120
                            bottomPadding: 0
                            verticalAlignment: VerticalAlignment.Bottom
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            Container {
                             //   minWidth: 568
                              //  maxWidth: 568
                                preferredWidth: 568
                                Label {
                                    text: qsTr(ListItemData.line_name)
                                }
                                Label {
                                    text: qsTr(ListItemData.start_station + "  -  " + ListItemData.end_station)
                                    textStyle.fontStyle: FontStyle.Italic
                                    textStyle.fontSize: FontSize.Small
                                }
                            }
                            Container {
                                rightPadding: 0
                                horizontalAlignment: HorizontalAlignment.Right
                                verticalAlignment: VerticalAlignment.Center
                              //  background: Color.Blue
                                
                                /*Button {
                                    imageSource: "asset:///images/ic_delete.png"
                                    maxWidth: 70
                                    onClicked: {
                                        rootItem.ListItem.view.networkBus.deleteRecord(ListItemData.record_id)
                                    }
                                }*/
                                ImageButton {
                                 defaultImageSource: "asset:///images/ic_clear.png"
                               //  maxWidth: 70
                                 onClicked: {
                                 rootItem.ListItem.view.networkBus.deleteRecord(ListItemData.record_id)
                                 }
                                 }
                            }
                            
                            
                        }
                        
                        Divider {
                        
                        }
                    }
                
                }
            
            ]
        }
    }
    }
    attachedObjects: ComponentDefinition {
        id: pageDefinition;
        source: "resultPage.qml"
    }
}
attachedObjects: [
    NetworkBus {
        id: networkBus
    }
]

}