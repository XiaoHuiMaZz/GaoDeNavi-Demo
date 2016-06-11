//
//  NearBySearchViewController.m
//  高德地图03
//
//  Created by ma c on 16/6/5.
//  Copyright © 2016年 bjsxt. All rights reserved.
//

#import "ViewController.h"
#import <MAMapKit/MAMapKit.h>
#import <AMapSearchKit/AMapSearchKit.h>
#import <AMapNaviKit/AMapNaviKit.h>
#import "DriveDaoHangViewController.h"

@interface ViewController ()<MAMapViewDelegate, AMapSearchDelegate, UITableViewDelegate, UITableViewDataSource>

{
    MAMapView *_mapView;
    AMapSearchAPI *_search;
}

//保存兴趣点的数组
@property (strong, nonatomic) NSArray *arr;

@property (strong, nonatomic) UITableView *tableview;

//用户坐标
@property (strong, nonatomic) MAUserLocation *userLocation;

@end

@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    [self initMapVIew];
    [self.view addSubview:self.tableview];
    
}

//创建mapview和searchApi
- (void)initMapVIew
{
    _mapView = [[MAMapView alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(self.view.bounds), CGRectGetHeight(self.view.bounds))];
    _mapView.delegate = self;
    //[self.view addSubview:_mapView];
    [_mapView setUserTrackingMode: MAUserTrackingModeFollow animated:YES];
    _mapView.showsUserLocation = YES;
    _mapView.customizeUserLocationAccuracyCircleRepresentation = YES;
    //初始化检索对象
    _search = [[AMapSearchAPI alloc] init];
    _search.delegate = self;
}

//位置更新回调方法
-(void)mapView:(MAMapView *)mapView didUpdateUserLocation:(MAUserLocation *)userLocation updatingLocation:(BOOL)updatingLocation
{
    if(updatingLocation)
    {
        //取出当前位置的坐标
//        NSLog(@"latitude : %f,longitude: %f",userLocation.coordinate.latitude,userLocation.coordinate.longitude);
        self.userLocation = userLocation;
        /**
         
         * 在这里发起请求获取数据
         
         
         */
        //构造AMapPOIAroundSearchRequest对象，设置周边请求参数
        AMapPOIAroundSearchRequest *request = [[AMapPOIAroundSearchRequest alloc] init];
        request.location = [AMapGeoPoint locationWithLatitude:userLocation.coordinate.latitude longitude:userLocation.coordinate.longitude];
        request.keywords = @"加油站";
        // types属性表示限定搜索POI的类别，默认为：餐饮服务|商务住宅|生活服务
        // POI的类型共分为20种大类别，分别为：
        // 汽车服务|汽车销售|汽车维修|摩托车服务|餐饮服务|购物服务|生活服务|体育休闲服务|
        // 医疗保健服务|住宿服务|风景名胜|商务住宅|政府机构及社会团体|科教文化服务|
        // 交通设施服务|金融保险服务|公司企业|道路附属设施|地名地址信息|公共设施
        request.types = @"汽车服务|交通设施服务";
        request.sortrule = 0;
        request.requireExtension = YES;
        //发起周边搜索
        [_search AMapPOIAroundSearch: request];
    }
}

//实现POI搜索对应的回调函数
- (void)onPOISearchDone:(AMapPOISearchBaseRequest *)request response:(AMapPOISearchResponse *)response
{
    if(response.pois.count == 0)
    {
        return;
    }
    //获取数据源
    self.arr = response.pois;
    //刷新表格
    [self.tableview reloadData];
    
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.arr.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 60;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:nil];
    
    
    AMapPOI *poi = self.arr[indexPath.row];
    
    cell.textLabel.text = poi.name;
    
    cell.detailTextLabel.text = poi.address;
    
    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    AMapPOI *poi = self.arr[indexPath.row];
    DriveDaoHangViewController *vc = [[DriveDaoHangViewController alloc] init];
    //给起点设置坐标
    vc.startPoint = [AMapNaviPoint locationWithLatitude:self.userLocation.location.coordinate.latitude longitude:self.userLocation.location.coordinate.longitude];
    //给终点设置坐标
    vc.endPoint = [AMapNaviPoint locationWithLatitude:poi.location.latitude longitude:poi.location.longitude];
    //跳转到导航界面
    [self presentViewController:vc animated:YES completion:nil];
    
}

//懒加载表格
- (UITableView *)tableview
{
    if (!_tableview) {
        _tableview = [[UITableView alloc] initWithFrame:self.view.frame style:UITableViewStylePlain];
        _tableview.delegate = self;
        _tableview.dataSource = self;
        
    }
    return _tableview;
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    if ([error code] == kCLErrorDenied)
    {
        //访问被拒绝
        NSLog(@"%@",error);
    }
    if ([error code] == kCLErrorLocationUnknown) {
        //无法获取位置信息
        NSLog(@"%@",error);
    }
}
@end
