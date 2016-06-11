//
//  DriveDaoHangViewController.h
//  高德地图03
//
//  Created by ma c on 16/6/7.
//  Copyright © 2016年 bjsxt. All rights reserved.
//

#import <UIKit/UIKit.h>


@class AMapNaviPoint;
@interface DriveDaoHangViewController : UIViewController

///起点坐标
@property (nonatomic, strong) AMapNaviPoint *startPoint;

///终点坐标
@property (nonatomic, strong) AMapNaviPoint *endPoint;

@end
