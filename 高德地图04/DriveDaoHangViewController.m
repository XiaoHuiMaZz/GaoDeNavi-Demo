//
//  DriveDaoHangViewController.m
//  高德地图03
//
//  Created by ma c on 16/6/7.
//  Copyright © 2016年 bjsxt. All rights reserved.
//

#import "DriveDaoHangViewController.h"
#import <AMapNaviKit/AMapNaviKit.h>
#import "SpeechSynthesizer.h"

@interface DriveDaoHangViewController ()<AMapNaviDriveViewDelegate, AMapNaviDriveManagerDelegate>
//导航管理类
@property (strong, nonatomic) AMapNaviDriveManager *driveManager;

//导航视图
@property (strong, nonatomic) AMapNaviDriveView *driveView;


@end

@implementation DriveDaoHangViewController

//隐藏导航栏
- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = YES;
    self.navigationController.toolbarHidden = YES;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    //导航视图
    self.driveView = [[AMapNaviDriveView alloc] init];
    self.driveView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
    //车头朝北
    self.driveView.trackingMode = AMapNaviViewTrackingModeCarNorth;
    /**
     *  是否显示路口放大图,默认YES
     */
    self.driveView.showCrossImage = NO;
    
    [self.driveView setDelegate:self];
    
    [self.driveView setFrame:self.view.bounds];
    
    [self.view addSubview:self.driveView];
    
    self.driveManager = [[AMapNaviDriveManager alloc] init];

    self.driveManager.delegate = self;
    [self.driveManager addDataRepresentative:self.driveView];
    //为了方便展示,选择了固定的起终点
//    self.startPoint = [AMapNaviPoint locationWithLatitude:39.989773 longitude:116.479872];
//    self.endPoint   = [AMapNaviPoint locationWithLatitude:39.995839 longitude:116.451204];
    [self.driveManager calculateDriveRouteWithStartPoints:@[self.startPoint] endPoints:@[self.endPoint] wayPoints:nil drivingStrategy:AMapNaviDrivingStrategyShortDistance];
}


/**
 *  驾车路径规划成功后的回调函数
 */
- (void)driveManagerOnCalculateRouteSuccess:(AMapNaviDriveManager *)driveManager
{
    
    //发起模拟导航（实时导航换成 startGPSNavi）
    [self.driveManager startEmulatorNavi];
}

/**
 *  导航播报信息回调函数
 *
 *  @param soundString 播报文字
 *  @param soundStringType 播报类型,参考AMapNaviSoundType
 */
- (void)driveManager:(AMapNaviWalkManager *)walkManager playNaviSoundString:(NSString *)soundString soundStringType:(AMapNaviSoundType)soundStringType
{
    //语音播报
    [[SpeechSynthesizer sharedSpeechSynthesizer] speakString:soundString];
}

/**
 *  导航界面关闭按钮点击时的回调函数
 */
- (void)driveViewCloseButtonClicked:(AMapNaviWalkView *)walkView
{
    //停止导航
    [self.driveManager stopNavi];
    //移除导航界面
    [self.driveManager removeDataRepresentative:self.driveView];
    
    //停止语音
    [[SpeechSynthesizer sharedSpeechSynthesizer] stopSpeak];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}


- (void)driveViewTrunIndicatorViewTapped:(AMapNaviDriveView *)driveView
{
    if (self.driveView.showMode == AMapNaviDriveViewShowModeCarPositionLocked)
    {
        [self.driveView setShowMode:AMapNaviDriveViewShowModeNormal];
    }
    else if (self.driveView.showMode == AMapNaviDriveViewShowModeNormal)
    {
        [self.driveView setShowMode:AMapNaviDriveViewShowModeOverview];
    }
    else if (self.driveView.showMode == AMapNaviDriveViewShowModeOverview)
    {
        [self.driveView setShowMode:AMapNaviDriveViewShowModeCarPositionLocked];
    }
}

@end
