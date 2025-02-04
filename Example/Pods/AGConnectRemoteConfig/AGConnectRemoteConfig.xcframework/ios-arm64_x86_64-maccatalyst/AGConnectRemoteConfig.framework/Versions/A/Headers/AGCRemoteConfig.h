//
//  Copyright (c) Huawei Technologies Co., Ltd. 2020. All rights reserved
//

#import <Foundation/Foundation.h>
#import <HMFoundation/HMFoundation.h>
#import "AGCConfigValues.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 远程配置获取的value值的来源
 */
typedef NS_ENUM(NSInteger, AGCRemoteConfigSource) {
    /**
     * 获取的value值是类型初始值
     */
    AGCRemoteConfigSourceInitial,

    /**
     * 获取的value值是本地默认值
     */
    AGCRemoteConfigSourceLocal,

    /**
     * 获取的value值是云端默认值
     */
    AGCRemoteConfigSourceRemote
};

/**
 * AGConnect RemoteConfig SDK 入口类
 *
 */
@interface AGCRemoteConfig : NSObject

/**
 * 是否可以收集用户隐私
 * @return bool 是否允许手机用户个人隐私 默认为YES
 */
@property (nonatomic, assign) bool enableCollectionUserPrivacy;

/**
 * 获取AGCRemoteConfig实例
 * @return AGCRemoteConfig实例
 */
+ (instancetype)sharedInstance;

/**
 * 设置默认参数值
 * plist文件仅支持Dictionary格式，配置项type类型支持：String、Number、Boolean。
 * @param plistName plist文件名
 */
- (void)applyDefaultsPlistFile:(NSString *)plistName;

/**
 * 设置默认参数
 * @param defaults 以NSDictionary形式传入，参数类型支持NSString、NSNumber。
 */
- (void)applyDefaults:(NSDictionary<NSString *, id> *)defaults;

/**
 * 自定义属性 获取和更新云端配置数据到本地
 * @param customAttributes 以Dictionary形式传入。
 */
- (void)setCustomAttributes:(NSDictionary<NSString *, id> *)customAttributes;

/**
 * 获取自定义属性 
 * 。
 */
- (NSDictionary<NSString *, id> *)getCustomAttributes;

/**
 * 生效配置参数
 * @param values 从fetch方法中返回的ConfigValues值
 */
- (void)apply:(AGCConfigValues *)values;

/**
 * 获取最近一次拉取成功的缓存数据
 * @return 返回上次缓存的configValues值
 */
- (AGCConfigValues *)loadLastFetched;

/**
 * 从云测拉取最新的配置数据，拉取默认间隔12小时，12小时内返回缓存数据
 * @return 拉取结果的异步任务
 */
- (HMFTask<AGCConfigValues *> *)fetch;

/**
 * 从云测拉取最新的配置数据，由参数传入间隔时间，间隔内返回缓存数据
 * @param intervalSeconds 拉取数据的间隔时间，单位是秒
 * @return 拉取结果的异步任务
 */
- (HMFTask<AGCConfigValues *> *)fetch:(NSTimeInterval)intervalSeconds;

/**
 * 返回Key对应的BOOL类型的Value值
 * @param key 远程配置参数Key值
 * @return 对应的value值，若不包含Key则返回默认值
 */
- (BOOL)valueAsBool:(NSString *)key NS_SWIFT_NAME(valueAsBool(key:));

/**
 * 返回Key对应的NSNumber类型的Value值
 * @param key 远程配置参数Key值
 * @return 对应的value值，若不包含Key则返回默认值
 */
- (NSNumber *)valueAsNumber:(NSString *)key NS_SWIFT_NAME(valueAsNumber(key:));

/**
 * 返回Key对应的NSString类型的Value值
 * @param key 远程配置参数Key值
 * @return 对应的value值，若不包含Key则返回默认值
 */
- (NSString *)valueAsString:(NSString *)key NS_SWIFT_NAME(valueAsString(key:));

/**
 * 返回Key对应的NSData类型的Value值
 * @param key 远程配置参数Key值
 * @return 对应的value值，若不包含Key则返回默认值
 */
- (NSData *)valueAsData:(NSString *)key NS_SWIFT_NAME(valueAsData(key:));

/**
 * 返回Key对应的来源
 * @param key 远程配置参数Key值
 * @return 数据来源
 */
- (AGCRemoteConfigSource)getSource:(NSString *)key;

/**
 * 返回默认值和云端值合并后的所有值
 * @return 返回NSDictionary对象
 */
- (NSDictionary<NSString *, id> *)getMergedAll;

/**
 * 清除所有的缓存数据，包括从云测拉取的数据和传入的默认值
 */
- (void)clearAll;

@end

NS_ASSUME_NONNULL_END
