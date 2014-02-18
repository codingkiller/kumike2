
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
        kind: TitleBarKind.FreeForm
        kindProperties: FreeFormTitleBarKindProperties {
            Container {
                id: firstContainer
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
                    imageSource: "asset:///images/ic_down.png"
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
  //      background: backgroundPaint.imagePaint
        attachedObjects: [
            ImagePaintDefinition {
                id: backgroundPaint
                imageSource: "asset:///images/sky1.jpg"
                
            }
        ]
        Container {
         topPadding: 50
        TextField {
            id: line_name
            preferredWidth: 440
            hintText: qsTr("请输入实时公交线路 ")
            
        //    text: qsTr("M264")
            input.onSubmitted: {
                if(searchButton.enabled)
                	searchButton.clicked()
            }
            validator: Validator {
                id: searchValidator
                mode: ValidationMode.Immediate
                errorMessage: qsTr("请输入实时公交线路 ")
                onValidate: {
                    if(line_name.text.trim().length == 0){
                        state = ValidationState.Invalid
                        searchButton.enabled = false;
                        return;
                    }
                    state = ValidationState.Valid
                    searchButton.enabled = true
                }
            }
            }
        Button {
            id: searchButton
            text: qsTr("查询")
            imageSource: "asset:///images/ic_search.png"
            maxWidth: 200
            enabled: searchValidator.valid
            onClicked: {
                if(searchValidator.valid)
                networkBus.get_lines_by_city(listDialog.value,line_name.text)
                var page = pageDefinition.createObject()
                navigationPane.push(page)
            }
            
        }
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight
        }
    }
        
    /*Container {//广告部分
        background: Color.Red
        preferredHeight: 300
    }*/
    Container {
        topPadding: 50
        maxHeight: 800
        Label {
            text: "常用线路"
            textStyle{
                fontWeight: FontWeight.W100
                fontSize: FontSize.Large
            }
        }
        /*Container {
            background: Color.Blue
            preferredHeight: 2
            preferredWidth: 768
        }*/
        Divider {
            
        }
        ListView {
            property NetworkBus networkBus : networkBus
            property TextField line_name : line_name
            property Button searchButton : searchButton
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
                        Container {
                            bottomPadding: 0
                            verticalAlignment: VerticalAlignment.Bottom
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            Container {
                                preferredWidth: 618
                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight
                                }
                                Label {
                                    preferredWidth: 100
                                    text: qsTr(ListItemData.line_name)
                                }
                                Label {
                                    text: qsTr(ListItemData.start_station + "-" + ListItemData.end_station)
                                    textStyle.fontStyle: FontStyle.Italic
                                    textStyle.fontSize: FontSize.XSmall
                                }
                            }
                            Container {
                                maxHeight: 50
                                maxWidth: 50
                                rightPadding: 0
                                horizontalAlignment: HorizontalAlignment.Right
                                verticalAlignment: VerticalAlignment.Center
                                layout: StackLayout {
                                    orientation: LayoutOrientation.RightToLeft
                                }
                                ImageButton {
                                    maxHeight: 50
                                    maxWidth: 50
                                 defaultImageSource: "asset:///images/ic_clear.png"
                                 onClicked: {
                                 rootItem.ListItem.view.networkBus.deleteRecord(ListItemData.record_id)
                                 rootItem.visible = false;
                                 }
                                 }
                            }
                        }
                        Divider {
                        }
                    }
                }
            ]
            onTriggered: {
                var thisLineName = networkBus.localDataModel.data(indexPath).line_name;
                line_name.setText(thisLineName);
                networkBus.get_lines_by_city(listDialog.value,line_name.text);
                var page = pageDefinition.createObject();
                navigationPane.push(page);

                
                
            //    line_name.text = networkBus.localDataModel.data(indexPath).line_name;
            //    console.log("hahahaha:"+line_name.text);
            //    searchButton.clicked();
            }
        }
        /*Container {
            background: Color.Blue
            preferredHeight: 2
            preferredWidth: 768
        }*/
        Divider {
            
        }
    }
    Container {
	preferredWidth: 668
	horizontalAlignment: HorizontalAlignment.Center
	verticalAlignment: VerticalAlignment.Center
	topPadding: 50
        Button {
            text: qsTr("查看所有线路 ")
            preferredWidth: 668
            onClicked: {
                networkBus.get_all_line(listDialog.value)
                var page = allstations.createObject()
                navigationPane.push(page)

            }
        }
        attachedObjects: ComponentDefinition {
            id: allstations;
            source: "allline.qml"
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