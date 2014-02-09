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
                    text: "酷米客公交"
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
                    topPadding: 50
                    bottomPadding: 0
                    rightPadding: 0
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
                            includeRememberMe: true
                            rememberMeChecked: true
                            
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
        background: Color.Blue
    //    maxHeight: 500
     //   topPadding: 300
    //    topMargin: 300
    //	verticalAlignment: VerticalAlignment.Bottom
        bottomPadding: 0
        Container {
         //   bottomPadding: 0
         //   bottomMargin: 0
         //   verticalAlignment: VerticalAlignment.Bottom
         topPadding: 100
         leftPadding: 50
         maxHeight: 700
         minHeight: 300
        TextField {
            id: line_name
            maxWidth: 440
            hintText: "请输入实时公交线路"
        }
        Button {
        	id: button
        	text: "查询"
        	maxWidth: 200
        	onClicked: {
                networkBus.get_lines_by_city(listDialog.value,line_name.text)
                busResultSheet.open();
         }
        }
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight
        }
        Label {
            id: errorInfo
            text: networkBus.buslineText
        }
    }
        
    
    Container {
        background: Color.Cyan
      //  verticalAlignment: VerticalAlignment.Bottom
    //    bottomPadding: 0
     //   visible: true
        leftPadding: 50
        rightPadding: 50
        Label {
            text: "常用线路"
            textStyle{
                textAlign: TextAlign.Center
            }
        }

            Divider {

            }
            Label {
            id: timeInfo
            text: "起止时间"
        }
    }
    attachedObjects: [
        NetworkBus {
            id: networkBus
            
        }
    ]
        
    }
    attachedObjects: [
        Sheet {
            id: busResultSheet
            
            content: Page {
                titleBar: TitleBar {
                    kind: TitleBarKind.FreeForm
                    kindProperties: FreeFormTitleBarKindProperties {
                        Container {
                            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
                            topPadding: 20
                            verticalAlignment: VerticalAlignment.Bottom
                            horizontalAlignment: HorizontalAlignment.Center
                            ImageView {
                                imageSource: "asset:///images/ic_previous.png"
                                horizontalAlignment: HorizontalAlignment.Left
                                onTouch: {
                                    busResultSheet.close();
                                }
                            }
                            Label {
                                text: networkBus.line_name
                                textStyle {
                                    color: Color.White
                                    fontSize: FontSize.XLarge
                                    textAlign: TextAlign.Right
                                }
                                maxWidth: 400
                                horizontalAlignment: HorizontalAlignment.Right
                                layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                            }
                        
                        }
                    }
                }
                Container {
                    Container {
                        layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
                        topPadding: 20
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Center
                       
                        SegmentedControl {
                            id: selectLine
                            Option {
                                value: 0
                                text: "开往"+networkBus.to_station_one
                            }
                            Option {
                                value: 1
                                text: "开往"+networkBus.to_station_two
                            }
                            //  accessibility.name: "TODO: Add property content"
                            onSelectedIndexChanged: {
                                networkBus.changeBusLine(selectedValue)
                            }
                        }
                    }
                    
                    Divider {
                     //   visible: true
                     //   accessibility.name: "TODO: Add property content"
                    }
                    Container {
                        layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
                        topPadding: 20
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Center
                        minHeight: 800
                    }
                    Container {
                        layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
                        topPadding: 20
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Center
                        Label {
                            text: networkBus.start_station+"首末班"+networkBus.begin_time+"-"+networkBus.end_time+" 全程"+networkBus.price+"元"
                        }
                        
                    }
                }
                actions: [  
                    ActionItem {  
                        title: "返回"  
                        ActionBar.placement: ActionBarPlacement.OnBar
                        onTriggered: {  
                            busResultSheet.close();  
                        }  
                    }  
                ]   
            }
        }
    ]
}
