//
//  MAGeometry.h
//  MAMapKit
//
//  Created by AutoNavi.
//  Copyright (c) 2013年 AutoNavi. All rights reserved.
//
#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct {
        CLLocationCoordinate2D northEast;
        CLLocationCoordinate2D southWest;
    } MACoordinateBounds;
    
    typedef struct {
        CLLocationDegrees latitudeDelta;
        CLLocationDegrees longitudeDelta;
    } MACoordinateSpan;
    
    typedef struct {
        CLLocationCoordinate2D center;
        MACoordinateSpan span;
    } MACoordinateRegion;
    
    static inline MACoordinateBounds MACoordinateBoundsMake(CLLocationCoordinate2D northEast,CLLocationCoordinate2D southWest)
    {
        return (MACoordinateBounds){northEast, southWest};
    }
    
    static inline MACoordinateSpan MACoordinateSpanMake(CLLocationDegrees latitudeDelta, CLLocationDegrees longitudeDelta)
    {
        return (MACoordinateSpan){latitudeDelta, longitudeDelta};
    }
    
    static inline MACoordinateRegion MACoordinateRegionMake(CLLocationCoordinate2D centerCoordinate, MACoordinateSpan span)
    {
        return (MACoordinateRegion){centerCoordinate, span};
    }

    /**
     *  生成一个新的MACoordinateRegion
     *
     *  @param centerCoordinate   中心点坐标
     *  @param latitudinalMeters  垂直跨度(单位 米)
     *  @param longitudinalMeters 水平跨度(单位 米)
     *
     *  @return 新的MACoordinateRegion
     */
    extern MACoordinateRegion MACoordinateRegionMakeWithDistance(CLLocationCoordinate2D centerCoordinate, CLLocationDistance latitudinalMeters, CLLocationDistance longitudinalMeters);
    
    /**
     *  平面投影坐标结构定义
     */
    typedef struct {
        double x;
        double y;
    } MAMapPoint;
    
    /**
     *  平面投影大小结构定义
     */
    typedef struct {
        double width;
        double height;
    } MAMapSize;
    
    /**
     *  平面投影矩形结构定义
     */
    typedef struct {
        MAMapPoint origin;
        MAMapSize size;
    } MAMapRect;
    
    /**
     *  比例关系:MAZoomScale = Screen Point / MAMapPoint, 当MAZoomScale = 1时, 1 screen point = 1 MAMapPoint, 当MAZoomScale = 0.5时, 1 screen point = 2 MAMapPoints
     */
    typedef double MAZoomScale;
    
    /**
     *  const常量定义
     */
    extern const MAMapSize MAMapSizeWorld;
    
    extern const MAMapRect MAMapRectWorld;
    
    extern const MAMapRect MAMapRectNull;
    
    extern const MAMapRect MAMapRectZero;
    
    /**
     *  经纬度坐标转平面投影坐标
     *
     *  @param coordinate 要转化的经纬度坐标
     *
     *  @return 平面投影坐标
     */
    extern MAMapPoint MAMapPointForCoordinate(CLLocationCoordinate2D coordinate);
    
    /**
     *  平面投影坐标转经纬度坐标
     *
     *  @param mapPoint 要转化的平面投影坐标
     *
     *  @return 经纬度坐标
     */
    extern CLLocationCoordinate2D MACoordinateForMapPoint(MAMapPoint mapPoint);
    
    /**
     *  平面投影矩形转region
     *
     *  @param rect 要转化的平面投影矩形
     *
     *  @return region
     */
    extern MACoordinateRegion MACoordinateRegionForMapRect(MAMapRect rect);
    
    /**
     *  region转平面投影矩形
     *
     *  @param region region 要转化的region
     *
     *  @return 平面投影矩形
     */
    extern MAMapRect MAMapRectForCoordinateRegion(MACoordinateRegion region);
    
    /*!
     @brief 单位投影的距离
     */
    
    /**
     *  单位投影的距离
     *
     *  @param latitude 经纬度
     *
     *  @return 距离
     */
    extern CLLocationDistance MAMetersPerMapPointAtLatitude(CLLocationDegrees latitude);
    
    /**
     *  1米对应的投影
     *
     *  @param latitude 经纬度
     *
     *  @return 1米对应的投影
     */
    extern double MAMapPointsPerMeterAtLatitude(CLLocationDegrees latitude);

    /**
     *  投影两点之间的距离
     *
     *  @param a a点
     *  @param b b点
     *
     *  @return 距离
     */
    extern CLLocationDistance MAMetersBetweenMapPoints(MAMapPoint a, MAMapPoint b);
    
    /**
     *  经纬度间的面积(单位 平方米)
     *
     *  @param northEast 东北经纬度
     *  @param southWest 西南经纬度
     *
     *  @return 面积
     */
    extern double MAAreaBetweenCoordinates(CLLocationCoordinate2D northEast, CLLocationCoordinate2D southWest);
    
    /*!
     @brief 获取Inset后的MAMapRect
     */
    
    /**
     *  获取Inset后的MAMapRect
     *
     *  @param rect rect
     *  @param dx   x点
     *  @param dy   y点
     *
     *  @return MAMapRect
     */
    extern MAMapRect MAMapRectInset(MAMapRect rect, double dx, double dy);
    
    /**
     *  合并两个MAMapRect
     *
     *  @param rect1 rect1
     *  @param rect2 rect2
     *
     *  @return 合并后的rect
     */
    extern MAMapRect MAMapRectUnion(MAMapRect rect1, MAMapRect rect2);
    
    /**
     *  判断size1是否包含size2
     *
     *  @param size1 size1
     *  @param size2 size2
     *
     *  @return 判断结果
     */
    extern BOOL MAMapSizeContainsSize(MAMapSize size1, MAMapSize size2);
    
    /**
     *  判断点是否在矩形内
     *
     *  @param rect  矩形rect
     *  @param point 点
     *
     *  @return 判断结果
     */
    extern BOOL MAMapRectContainsPoint(MAMapRect rect, MAMapPoint point);
    
    /**
     *  判断两矩形是否相交
     *
     *  @param rect1 rect1
     *  @param rect2 rect2
     *
     *  @return 判断结果
     */
    extern BOOL MAMapRectIntersectsRect(MAMapRect rect1, MAMapRect rect2);
    
    /**
     *  判断矩形rect1是否包含矩形rect2
     *
     *  @param rect1 rect1
     *  @param rect2 rect2
     *
     *  @return 判断结果
     */
    extern BOOL MAMapRectContainsRect(MAMapRect rect1, MAMapRect rect2);
    
    /**
     *  判断点是否在圆内
     *
     *  @param point  点
     *  @param center 圆的中心点
     *  @param radius 圆的半径
     *
     *  @return 判断结果
     */
    extern BOOL MACircleContainsPoint(MAMapPoint point, MAMapPoint center, double radius);
    
    /**
     *  判断经纬度点是否在圆内
     *
     *  @param point  经纬度
     *  @param center 圆的中心经纬度
     *  @param radius 圆的半径
     *
     *  @return 判断结果
     */
    extern BOOL MACircleContainsCoordinate(CLLocationCoordinate2D point, CLLocationCoordinate2D center, double radius);
    
    /**
     *  判断点是否在多边形内
     *
     *  @param point   点
     *  @param polygon 多边形
     *  @param count   多边形点的数量
     *
     *  @return 判断结果
     */
    extern BOOL MAPolygonContainsPoint(MAMapPoint point, MAMapPoint *polygon, NSUInteger count);

    /**
     *  判断经纬度点是否在多边形内
     *
     *  @param point   经纬度点
     *  @param polygon 多边形
     *  @param count   多边形点的数量
     *
     *  @return <#return value description#>
     */
    extern BOOL MAPolygonContainsCoordinate(CLLocationCoordinate2D point, CLLocationCoordinate2D *polygon, NSUInteger count);
    
    /**
     *  取在lineStart和lineEnd组成的线段上距离point距离最近的点
     *
     *  @param lineStart 线段起点
     *  @param lineEnd   线段终点
     *  @param point     测试点
     *
     *  @return 距离point最近的点坐标
     */
    extern MAMapPoint MAGetNearestMapPointFromLine(MAMapPoint lineStart, MAMapPoint lineEnd, MAMapPoint point);
    
    /**
     *  获取墨卡托投影切块回调block，如果是无效的映射，则返回(-1, -1, 0, 0, 0, 0)
     *
     *  @param offsetX 左上点距离所属tile的位移X, 单位像素
     *  @param offsetY 左上点距离所属tile的位移Y, 单位像素
     *  @param minX    覆盖tile的最小x
     *  @param maxX    覆盖tile的最大x
     *  @param minY    覆盖tile的最小y
     *  @param maxY    覆盖tile的最大y
     */
    typedef void (^AMapTileProjectionBlock)(int offsetX, int offsetY, int minX, int maxX, int minY, int maxY);
    
    /**
     *  根据所给经纬度区域获取墨卡托投影切块信息
     *
     *  @param bounds         经纬度区域
     *  @param levelOfDetails 对应缩放级别, 取值0-20
     *  @param tileProjection 返回的切块信息block
     */
    extern void MAGetTileProjectionFromBounds(MACoordinateBounds bounds, int levelOfDetails, AMapTileProjectionBlock tileProjection);
    
    
    static inline MAMapPoint MAMapPointMake(double x, double y)
    {
        return (MAMapPoint){x, y};
    }
    
    static inline MAMapSize MAMapSizeMake(double width, double height)
    {
        return (MAMapSize){width, height};
    }
    
    static inline MAMapRect MAMapRectMake(double x, double y, double width, double height)
    {
        return (MAMapRect){MAMapPointMake(x, y), MAMapSizeMake(width, height)};
    }
    
    static inline double MAMapRectGetMinX(MAMapRect rect)
    {
        return rect.origin.x;
    }
    
    static inline double MAMapRectGetMinY(MAMapRect rect)
    {
        return rect.origin.y;
    }
    
    static inline double MAMapRectGetMidX(MAMapRect rect)
    {
        return rect.origin.x + rect.size.width / 2.0;
    }
    
    static inline double MAMapRectGetMidY(MAMapRect rect)
    {
        return rect.origin.y + rect.size.height / 2.0;
    }
    
    static inline double MAMapRectGetMaxX(MAMapRect rect)
    {
        return rect.origin.x + rect.size.width;
    }
    
    static inline double MAMapRectGetMaxY(MAMapRect rect)
    {
        return rect.origin.y + rect.size.height;
    }
    
    static inline double MAMapRectGetWidth(MAMapRect rect)
    {
        return rect.size.width;
    }
    
    static inline double MAMapRectGetHeight(MAMapRect rect)
    {
        return rect.size.height;
    }
    
    static inline BOOL MAMapPointEqualToPoint(MAMapPoint point1, MAMapPoint point2) {
        return point1.x == point2.x && point1.y == point2.y;
    }
    
    static inline BOOL MAMapSizeEqualToSize(MAMapSize size1, MAMapSize size2) {
        return size1.width == size2.width && size1.height == size2.height;
    }
    
    static inline BOOL MAMapRectEqualToRect(MAMapRect rect1, MAMapRect rect2) {
        return
        MAMapPointEqualToPoint(rect1.origin, rect2.origin) &&
        MAMapSizeEqualToSize(rect1.size, rect2.size);
    }
    
    static inline BOOL MAMapRectIsNull(MAMapRect rect) {
        return isinf(rect.origin.x) || isinf(rect.origin.y);
    }
    
    static inline BOOL MAMapRectIsEmpty(MAMapRect rect) {
        return MAMapRectIsNull(rect) || (rect.size.width == 0.0 && rect.size.height == 0.0);
    }
    
    static inline NSString *MAStringFromMapPoint(MAMapPoint point) {
        return [NSString stringWithFormat:@"{%.1f, %.1f}", point.x, point.y];
    }
    
    static inline NSString *MAStringFromMapSize(MAMapSize size) {
        return [NSString stringWithFormat:@"{%.1f, %.1f}", size.width, size.height];
    }
    
    static inline NSString *MAStringFromMapRect(MAMapRect rect) {
        return [NSString stringWithFormat:@"{%@, %@}", MAStringFromMapPoint(rect.origin), MAStringFromMapSize(rect.size)];
    }
    
    /// 坐标类型枚举
    typedef NS_ENUM(NSUInteger, MACoordinateType)
    {
        MACoordinateTypeBaidu = 0,  //!< Baidu
        MACoordinateTypeMapBar,     //!< MapBar
        MACoordinateTypeMapABC,     //!< MapABC
        MACoordinateTypeSoSoMap,    //!< SoSoMap
        MACoordinateTypeAliYun,     //!< AliYun
        MACoordinateTypeGoogle,     //!< Google
        MACoordinateTypeGPS,        //!< GPS
    };
    
    /**
     *  转换目标经纬度为高德坐标系
     *
     *  @param coordinate 待转换的经纬度
     *  @param type       坐标系类型
     *
     *  @return 高德坐标系经纬度
     */
    extern CLLocationCoordinate2D MACoordinateConvert(CLLocationCoordinate2D coordinate, MACoordinateType type) __attribute((deprecated("已废弃，使用AMapFoundation中关于坐标转换的接口")));
    
    
#ifdef __cplusplus
}
#endif

@interface NSValue (NSValueMAGeometryExtensions)

+ (NSValue *)valueWithMAMapPoint:(MAMapPoint)mapPoint;
+ (NSValue *)valueWithMAMapSize:(MAMapSize)mapSize;
+ (NSValue *)valueWithMAMapRect:(MAMapRect)mapRect;
+ (NSValue *)valueWithMACoordinate:(CLLocationCoordinate2D)coordinate;

- (MAMapPoint)MAMapPointValue;
- (MAMapSize)MAMapSizeValue;
- (MAMapRect)MAMapRectValue;
- (CLLocationCoordinate2D)MACoordinateValue;

@end
