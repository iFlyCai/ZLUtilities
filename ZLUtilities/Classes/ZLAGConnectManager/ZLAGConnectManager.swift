//
//  ZLAGConnectManager.swift
//  ZLGitHubClient
//
//  Created by 朱猛 on 2024/2/24.
//  Copyright © 2024 ZM. All rights reserved.
//

import UIKit
import AGConnectCore
import AGConnectRemoteConfig
import AGConnectABTest
import HiAnalytics

public func ZLAGC() -> ZLAGConnectManager {
    ZLAGConnectManager.sharedInstance
}

@objc public class ZLAGConnectManager: NSObject {

    @objc public static let sharedInstance: ZLAGConnectManager = ZLAGConnectManager()
    
    var remoteConfig: AGCRemoteConfig?  /// 远程配置实例
    var remoteConfigSuccssTime: TimeInterval?
    var remoteConfigFailTime: TimeInterval?
    #if DEBUG
    let remoteConfigUpdateGap: TimeInterval = 15   /// DEBUG 环境远程配置更新时间间隔 15 s
    #else
    let remoteConfigUpdateGap: TimeInterval = 3600   /// 远程配置更新时间间隔 1 小时
    #endif
    var isLoadingRemoteConfig: Bool = false
    var fetchRemoteConfigBlock: ((Bool, TimeInterval, String) -> Void)?
    
    deinit {
        unregisterNotifications()
    }
    
    /// 启动华为监控/分析
    @objc public func setup() {
        
        AGCInstance.startUp()
        
        /// 华为分析 上报策略
        HiAnalytics.config()
        HiAnalytics.setReportPolicies([HAReportPolicy.onMoveBackground(),
                                       HAReportPolicy.onCacheThresholdPolicy(30),
                                       HAReportPolicy.onAppLaunch(),
                                       HAReportPolicy.onScheduledTime(100)]);
        
#if DEBUG
        NSLog("AAID: \(HiAnalytics.aaid())")
#endif
        
        /// 远程配置
        let config = AGCRemoteConfig.sharedInstance()
        config.apply(config.loadLastFetched())
        remoteConfig = config
        
        
        
        /// 请求远程配置
        fetchRemoteConfig()
        
        registerNotifications()
    }
    
    @objc func registerNotifications() {
        NotificationCenter.default.addObserver(self, selector: #selector(fetchNewRemoteConfigWhenDidBecomeActive), name: UIApplication.didBecomeActiveNotification, object: nil)
    }
    
    @objc func unregisterNotifications() {
        NotificationCenter.default.removeObserver(self, name: UIApplication.didBecomeActiveNotification, object: nil)
    }
}

// MARK: - remote config
public extension ZLAGConnectManager {
    
    @objc func setFetchRemoteConfig(completeBlock: @escaping (Bool, TimeInterval, String) -> Void) {
        fetchRemoteConfigBlock = completeBlock
    }
    
    @objc func fetchRemoteConfig() {
        isLoadingRemoteConfig = true
        let startTime = Date().timeIntervalSince1970
        remoteConfig?.fetch(0)
            .onSuccess(callback: { [weak self] configValue in
                guard let self, let configValue = configValue else { return }
                self.remoteConfig?.apply(configValue)
                let endTime = Date().timeIntervalSince1970
                self.remoteConfigSuccssTime = endTime
                self.isLoadingRemoteConfig = false
                self.fetchRemoteConfigBlock?(true,endTime - startTime,"")
            })
            .onFailure(callback: { [weak self] error in
                guard let self else { return }
                let endTime = Date().timeIntervalSince1970
                self.remoteConfigFailTime = endTime
                self.isLoadingRemoteConfig = false
                self.fetchRemoteConfigBlock?(false,endTime - startTime, error.localizedDescription)
            })
    }
    
    @objc dynamic func fetchNewRemoteConfigWhenDidBecomeActive() {
        let currentTime = Date().timeIntervalSince1970
        if let lastSuccessTime = remoteConfigSuccssTime,
           currentTime - lastSuccessTime > remoteConfigUpdateGap,
           !isLoadingRemoteConfig  {
            fetchRemoteConfig()
        }
    }
    
    @objc func checkBeforeUseRemoteConfig() {
        if remoteConfigSuccssTime == nil && !isLoadingRemoteConfig {
            fetchRemoteConfig()
        }
    }
    
    @objc func configAsBool(for key: String, defaultValue: Bool = false) -> Bool {
        checkBeforeUseRemoteConfig()
        return remoteConfig?.valueAsBool(key: key) ?? defaultValue
    }
    
    @objc func configAsInt(for key: String, defaultValue: Int = 0) -> Int {
        checkBeforeUseRemoteConfig()
        return remoteConfig?.valueAsNumber(key: key).intValue ?? defaultValue
    }
    
    @objc func configAsString(for key: String, defaultValue: String = "") -> String {
        checkBeforeUseRemoteConfig()
        return remoteConfig?.valueAsString(key: key) ?? defaultValue
    }
    
    @objc func configAsJsonObject(for key: String, defaultValue: [String:Any] = [:]) -> [String:Any] {
        checkBeforeUseRemoteConfig()
        let configData = remoteConfig?.valueAsData(key: key) ?? Data()
        if let jsonObject = try? JSONSerialization.jsonObject(with: configData) as? [String:Any] {
            return jsonObject
        } else {
            return defaultValue
        }
    }
}

// MARK: - Analyze
public extension ZLAGConnectManager {
    
    @objc func reportEvent(eventId: String, params: [String:Any]) {
        HiAnalytics.onEvent(eventId, setParams: params);
    }
    
}
