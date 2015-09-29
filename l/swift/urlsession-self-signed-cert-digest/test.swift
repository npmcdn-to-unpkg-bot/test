
// Need to implement NSURLSessionDelegate to handle server trust
// and NSURLSessionTaskDelegate to handle other chanllege
//
// see https://forums.developer.apple.com/thread/13423
// see https://developer.apple.com/library/prerelease/ios/documentation/Foundation/Reference/NSURLSessionTaskDelegate_protocol/index.html#//apple_ref/occ/intfm/NSURLSessionTaskDelegate/URLSession:task:didReceiveChallenge:completionHandler:


import Foundation
import Alamofire


class NotificationProvider : NSObject, NSURLSessionDelegate, NSURLSessionTaskDelegate {
    static let registerURL = "https://www.admininc.cn/api/register"
    static let authUserName = "admin"
    static let authPassword = "admin"
    

    func register(identity: String, _ device: String, _ token: String) {
        
        NSLog("register")
        let params = ["identity": identity, "device": device, "device_type": UIDevice.currentDevice().systemName, "token":token ]
        let credential = NSURLCredential(user: NotificationProvider.authUserName, password: NotificationProvider.authPassword, persistence: .Permanent)
        MyManager.sharedInstance.defaultManager.request(.POST, NotificationProvider.registerURL, parameters: params, encoding: .JSON)
            .authenticate(usingCredential: credential)
            .responseJSON { response in
                NSLog("json: \(response)")
        }
    }
    
    func registerWithSession(identity:String, _ devices:String, _ token:String) {
        let url: NSURL! = NSURL(string: NotificationProvider.registerURL)
        let request: NSMutableURLRequest = NSMutableURLRequest(URL: url)
        request.HTTPMethod = "POST"
        request.HTTPBody = ("identity=" + identity + "&device=" + devices + "&device_type="
            + UIDevice.currentDevice().systemName + "&token=" + token).dataUsingEncoding(NSUTF8StringEncoding)
        
        let configuration = NSURLSessionConfiguration.defaultSessionConfiguration()
        let session = NSURLSession(configuration: configuration, delegate:self, delegateQueue: NSOperationQueue.mainQueue())
        
        let task = session.dataTaskWithRequest(request,
            completionHandler: {
            (data, response, error) -> Void in
            if error == nil {
                let result = NSString(data: data!, encoding: NSASCIIStringEncoding)!
                NSLog("result %@", result)
            } else {
                NSLog("got rerror %@", error!)
            }
        })
        task.resume()
    }
    
    func URLSession(session: NSURLSession, didReceiveChallenge challenge: NSURLAuthenticationChallenge, completionHandler: (NSURLSessionAuthChallengeDisposition, NSURLCredential?) -> Void) {
        NSLog("DAFEI we receive challenge")
        if challenge.protectionSpace.authenticationMethod == NSURLAuthenticationMethodServerTrust {
            NSLog("we are doing ServerTrust")
            let trust: NSURLCredential = NSURLCredential(trust: challenge.protectionSpace.serverTrust!)
            completionHandler(NSURLSessionAuthChallengeDisposition.UseCredential, trust)
        } else if challenge.protectionSpace.authenticationMethod == NSURLAuthenticationMethodHTTPDigest {
            NSLog("We are doing Digest")
            let credential = NSURLCredential(user: NotificationProvider.authUserName,
                password: NotificationProvider.authPassword,
                persistence: NSURLCredentialPersistence.ForSession)
            completionHandler(NSURLSessionAuthChallengeDisposition.UseCredential, credential)
        } else {
            challenge.sender?.performDefaultHandlingForAuthenticationChallenge?(challenge)
        }
    }
    
    func URLSession(session: NSURLSession, task: NSURLSessionTask, didReceiveChallenge challenge: NSURLAuthenticationChallenge, completionHandler: (NSURLSessionAuthChallengeDisposition, NSURLCredential?) -> Void) {
        NSLog("DAFEI we receive TASK challenge")
        if challenge.protectionSpace.authenticationMethod == NSURLAuthenticationMethodServerTrust {
            NSLog("we are doing TASK ServerTrust")
            let trust: NSURLCredential = NSURLCredential(trust: challenge.protectionSpace.serverTrust!)
            completionHandler(NSURLSessionAuthChallengeDisposition.UseCredential, trust)
        } else if challenge.protectionSpace.authenticationMethod == NSURLAuthenticationMethodHTTPDigest {
            NSLog("We are doing TASK Digest")
            let credential = NSURLCredential(user: NotificationProvider.authUserName,
                password: NotificationProvider.authPassword,
                persistence: NSURLCredentialPersistence.ForSession)
            completionHandler(NSURLSessionAuthChallengeDisposition.UseCredential, credential)
        } else {
            challenge.sender?.performDefaultHandlingForAuthenticationChallenge?(challenge)
        }
    }
}