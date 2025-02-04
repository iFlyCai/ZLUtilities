//
//  Copyright (c) Huawei Technologies Co., Ltd. 2020. All rights reserved
//

#import <AGConnectCore/AGConnectCore.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Remote Config SDK的错误码
 */
typedef NS_ENUM(NSUInteger, AGCRemoteConfigErrorCode) {
    /**
     * 受到本地流控,请稍后重试
     */
    AGCRemoteConfigErrorCodeFetchThrottled = 1,

    /**
     * 系统错误，请联系华为技术人员
     */
    AGCRemoteConfigErrorCodeUnknown = 0x0c2a0001,

    /**
     * 应用未配置参数条件
     */
    AGCRemoteConfigErrorCodeRcsConfigEmpty = 0x0c2a0004,

    /**
     * 响应数据未改变
     */
    AGCRemoteConfigErrorCodeDataNotModified = 0x0c2a3001,
};

/**
 * Remote Config SDK的异常类
 */
@interface AGCRemoteConfigError : NSError

/**
 * 如果是本地流控错误，则返回流控剩余时间
 */
@property(nonatomic, readonly) NSTimeInterval throttleEndTime;

@end

NS_ASSUME_NONNULL_END
