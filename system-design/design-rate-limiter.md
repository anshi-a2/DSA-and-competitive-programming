# How to design a rate limiter 

In a network system, a rate limiter is used to control the rate of traffic sent by a client or a service. In the HTTP world, a rate limiter limits the number of client requests allowed to be sent over a specified period. If the API request count exceeds the threshold defined by the rate limiter, all the excess calls are blocked. Here are a few examples:

-  A user can write no more than 2 posts per second.
- You can create a maximum of 10 accounts per day from the same IP address.
- You can claim rewards no more than 5 times per week from the same device.

Before starting the design, we first look at the benefits of using an API rate limiter:

- Prevent resource starvation caused by Denial of Service (DoS) attack [1]. Almost all APIs published by large tech companies enforce some form of rate limiting. For example, Twitter limits the number of tweets to 300 per 3 hours. Google docs APIs have the following default limit: 300 per user per 60 seconds for read requests. A rate limiter prevents DoS attacks, either intentional or unintentional, by blocking the excess calls.

- Reduce cost. Limiting excess requests means fewer servers and allocating more resources to high priority APIs. Rate limiting is extremely important for companies that use paid third party APIs. For example, you are charged on a per-call basis for the following external APIs: check credit, make a payment, retrieve health records, etc. Limiting the number of calls is essential to reduce costs.

- Prevent servers from being overloaded. To reduce server load, a rate limiter is used to filter out excess requests caused by bots or users’ misbehavior


## Step 1 - Understand the problem and establish design scope

Rate limiting can be implemented using different algorithms, each with its pros and cons. The interactions between an interviewer and a candidate help to clarify the type of rate limiters we are trying to build


Candidate: What kind of rate limiter are we going to design? Is it a client-side rate limiter or server-side API rate limiter?

Interviewer: Great question. We focus on the server-side API rate limiter.

Candidate: Does the rate limiter throttle API requests based on IP, the user ID, or other properties?

Interviewer: The rate limiter should be flexible enough to support different sets of throttle rules.

Candidate: What is the scale of the system? Is it built for a startup or a big company with a large user base?
Interviewer: The system must be able to handle a large number of requests.

Candidate: Will the system work in a distributed environment?

Interviewer: Yes.

Candidate: Is the rate limiter a separate service or should it be implemented in application code?
Interviewer: It is a design decision up to you.

Candidate: Do we need to inform users who are throttled?
Interviewer: Yes.

### Requirements
Here is a summary of the requirements for the system:

  - Accurately limit excessive requests.
  - Low latency. The rate limiter should not slow down HTTP response time.
  - Use as little memory as possible.
  - Distributed rate limiting. The rate limiter can be shared across multiple servers or processes.
  - Exception handling. Show clear exceptions to users when their requests are throttled.
  - High fault tolerance. If there are any problems with the rate limiter (for example, a cache server goes offline), it does not affect the entire system.


## Step 2 - Propose high-level design and get buy-in

Let us keep things simple and use a basic client and server model for communication.

#### Where to put the rate limiter?
Intuitively, you can implement a rate limiter at either the client or server-side.

- Client-side implementation. Generally speaking, client is an unreliable place to enforce rate limiting because client requests can easily be forged by malicious actors. Moreover, we might not have control over the client implementation.

- Server-side implementation. Figure 4-1 shows a rate limiter that is placed on the server- side.


![image](https://user-images.githubusercontent.com/23625821/132120378-d579933f-556e-4cd3-8b63-8ef6d63b4d90.png)

Besides the client and server-side implementations, there is an alternative way. Instead of putting a rate limiter at the API servers, we create a rate limiter middleware, which throttles requests to your APIs. 

![image](https://user-images.githubusercontent.com/23625821/132120384-74c77aff-fda1-4cd5-b0ce-c712b840e0aa.png)

Assume our API allows 2 requests per second, and a client sends 3 requests to the server within a second. The first two requests are routed to API servers. However, the rate limiter middleware throttles the third request and returns a HTTP status code 429. The HTTP 429 response status code indicates a user has sent too many requests.

![image](https://user-images.githubusercontent.com/23625821/132120396-f3dd7e42-df2d-4c44-bf7b-3bdbfde5cbdf.png)


Cloud microservices [4] have become widely popular and rate limiting is usually implemented within a component called API gateway. API gateway is a fully managed
service that supports rate limiting, SSL termination, authentication, IP whitelisting, servicing static content, etc. For now, we only need to know that the API gateway is a middleware that supports rate limiting.

While designing a rate limiter, an important question to ask ourselves is: where should the rater limiter be implemented, on the server-side or in a gateway? There is no absolute answer.

It depends on your company’s current technology stack, engineering resources, priorities, goals, etc. Here are a few general guidelines:

- Evaluate your current technology stack, such as programming language, cache service, etc. Make sure your current programming language is efficient to implement rate limiting on the server-side.

- Identify the rate limiting algorithm that fits your business needs. When you implement everything on the server-side, you have full control of the algorithm. However, your choice might be limited if you use a third-party gateway.

- If you have already used microservice architecture and included an API gateway in the design to perform authentication, IP whitelisting, etc., you may add a rate limiter to the API gateway.

- Building your own rate limiting service takes time. If you do not have enough engineering resources to implement a rate limiter, a commercial API gateway is a better option.


## Algorithms for rate limiting

Rate limiting can be implemented using different algorithms, and each of them has distinct pros and cons. Even though this chapter does not focus on algorithms, understanding them at high-level helps to choose the right algorithm or combination of algorithms to fit our use cases. Here is a list of popular algorithms:

    • Token bucket
    • Leaking bucket
    • Fixed window counter
    • Sliding window log
    • Sliding window counter

#### Token bucket algorithm

The token bucket algorithm is widely used for rate limiting. It is simple, well understood andcommonly used by internet companies. Both Amazon and Stripe use this algorithm to throttle their API requests.

The token bucket algorithm work as follows:

- A token bucket is a container that has pre-defined capacity. 
- Tokens are put in the bucket at preset rates periodically. 
- Once the bucket is full, no more tokens are added. 
- The refiller puts 2 tokens into the bucket every second. Once the bucket is full, extra tokens will overflow

![image](https://user-images.githubusercontent.com/23625821/132120508-e55a0136-e72c-448c-a84f-bff662be24d7.png)

#### Leaking bucket algorithm

The leaking bucket algorithm is similar to the token bucket except that requests are processed at a fixed rate. It is usually implemented with a first-in-first-out (FIFO) queue. The algorithm works as follows:

  - When a request arrives, the system checks if the queue is full. If it is not full, the request is added to the queue.
  - Otherwise, the request is dropped.
  - Requests are pulled from the queue and processed at regular intervals.

![image](https://user-images.githubusercontent.com/23625821/132173606-16b92216-374c-4b89-9356-e807dae1618e.png)

Leaking bucket algorithm takes the following two parameters:

- Bucket size: it is equal to the queue size. The queue holds the requests to be processed at a fixed rate.
- Outflow rate: it defines how many requests can be processed at a fixed rate, usually in seconds.

Shopify, an ecommerce company, uses leaky buckets for rate-limiting

Pros:
- Memory efficient given the limited queue size.
- Requests are processed at a fixed rate therefore it is suitable for use cases that a stable outflow rate is needed.

Cons:
- A burst of traffic fills up the queue with old requests, and if they are not processed in time, recent requests will be rate limited.
- There are two parameters in the algorithm. It might not be easy to tune them properly.

#### Fixed window counter algorithm

Fixed window counter algorithm works as follows:

- The algorithm divides the timeline into fix-sized time windows and assign a counter for each window.
- Each request increments the counter by one.
- Once the counter reaches the pre-defined threshold, new requests are dropped until a new time window starts.

![image](https://user-images.githubusercontent.com/23625821/132173976-d45e74e0-b632-4508-a6e5-360126d7520b.png)

A major problem with this algorithm is that a burst of traffic at the edges of time windows could cause more requests than allowed quota to go through.


Pros:
- Memory efficient.
- Easy to understand.
- Resetting available quota at the end of a unit time window fits certain use cases.

Cons:
- Spike in traffic at the edges of a window could cause more requests than the allowed quota to go through.

#### Sliding window log algorithm

The fixed window counter algorithm has a major issue: it allows more requests to go through at the edges of a window. The sliding window log algorithm fixes the issue. It works as follows:

- The algorithm keeps track of request timestamps. Timestamp data is usually kept in cache, such as sorted sets of Redis. 
- When a new request comes in, remove all the outdated timestamps. Outdated timestamps are defined as those older than the start of the current time window.
- Add timestamp of the new request to the log.
- If the log size is the same or lower than the allowed count, a request is accepted. Otherwise, it is rejected.

![image](https://user-images.githubusercontent.com/23625821/132174782-401a4eeb-321b-40e1-94ce-1a6e7d4989a7.png)

In this example, the rate limiter allows 2 requests per minute. Usually, Linux timestamps are stored in the log. However, human-readable representation of time is used in our example for better readability.

- The log is empty when a new request arrives at 1:00:01. Thus, the request is allowed.• A new request arrives at 1:00:30, the timestamp 1:00:30 is inserted into the log. After the insertion, the log size is 2, not larger than the allowed count. Thus, the request is allowed.

- A new request arrives at 1:00:50, and the timestamp is inserted into the log. After the insertion, the log size is 3, larger than the allowed size 2. Therefore, this request is rejected even though the timestamp remains in the log.
- A new request arrives at 1:01:40. Requests in the range [1:00:40,1:01:40) are within the latest time frame, but requests sent before 1:00:40 are outdated. 
- Two outdated timestamps, 1:00:01 and 1:00:30, are removed from the log. After the remove operation, the log size becomes 2; therefore, the request is accepted.


Pros:
- Rate limiting implemented by this algorithm is very accurate. In any rolling window, requests will not exceed the rate limit.

Cons:
- The algorithm consumes a lot of memory because even if a request is rejected, its timestamp might still be stored in memory.

#### Sliding window counter algorithm

The sliding window counter algorithm is a hybrid approach that combines the fixed window counter and sliding window log. The algorithm can be implemented by two different approaches. We will explain one implementation in this section and provide reference for the other implementation at the end of the section.

![image](https://user-images.githubusercontent.com/23625821/132175266-5fd0470d-e71a-441a-a058-81d0dd942b49.png)

Assume the rate limiter allows a maximum of 7 requests per minute, and there are 5 requests in the previous minute and 3 in the current minute. For a new request that arrives at a 30% position in the current minute, the number of requests in the rolling window is calculated using the following formula:

- Requests in current window + requests in the previous window * overlap percentage of the rolling window and previous window.
- Using this formula, we get 3 + 5 * 0.7% = 6.5 request. Depending on the use case, the number can either be rounded up or down. 
- In our example, it is rounded down to 6. 

Since the rate limiter allows a maximum of 7 requests per minute, the current request can go through. However, the limit will be reached after receiving one more request.


Pros
- It smooths out spikes in traffic because the rate is based on the average rate of the previous window.
- Memory efficient.

Cons
- It only works for not-so-strict look back window. It is an approximation of the actual rate because it assumes requests in the previous window are evenly distributed. However, this problem may not be as bad as it seems. 
- According to experiments done by Cloudflare, only 0.003% of requests are wrongly allowed or rate limited among 400 million requests.


### High-level architecture

The basic idea of rate limiting algorithms is simple. At the high-level, we need a counter to keep track of how many requests are sent from the same user, IP address, etc. If the counter is larger than the limit, the request is disallowed. Where shall we store counters? Using the database is not a good idea due to slowness of disk access. In-memory cache is chosen because it is fast and supports time-based expiration strategy. For instance, Redis is a popular option to implement rate limiting. It is an in- memory store that offers two commands: INCR and EXPIRE.

- INCR: It increases the stored counter by 1.
- EXPIRE: It sets a timeout for the counter. If the timeout expires, the counter is automatically deleted.

![image](https://user-images.githubusercontent.com/23625821/132176124-60d39b6a-3532-452e-81f3-cd08d9d9587a.png)

- The client sends a request to rate limiting middleware.
- Rate limiting middleware fetches the counter from the corresponding bucket in Redis andchecks if the limit is reached or not.
    - If the limit is reached, the request is rejected.
    - If the limit is not reached, the request is sent to API servers. Meanwhile, the system increments the counter and saves it back to Redis.


### Step 3 - Design deep dive

The high-level design does not answer the following questions:

- How are rate limiting rules created? Where are the rules stored?
- How to handle requests that are rate limited?

In this section, we will first answer the questions regarding rate limiting rules and then go over the strategies to handle rate-limited requests. Finally, we will discuss rate limiting in distributed environment, a detailed design, performance optimization and monitoring.

#### Rate limiting rules

Lyft open-sourced their rate-limiting component. We will peek inside of the component and look at some examples of rate limiting rules:

```yaml
domain: messaging
descriptors:
- key: message_type
  Value: marketing
  rate_limit:
    unit: day
    requests_per_unit: 5

```

In the above example, the system is configured to allow a maximum of 5 marketing messages per day. Here is another example:

```yaml
domain: auth
descriptors:
- key: auth_type
  Value: login
  rate_limit:
    unit: minute
    requests_per_unit: 5

```

#### Exceeding the rate limit

In case a request is rate limited, APIs return a HTTP response code 429 (too many requests) to the client. Depending on the use cases, we may enqueue the rate-limited requests to be processed later. For example, if some orders are rate limited due to system overload, we may keep those orders to be processed later.


How does a client know whether it is being throttled? And how does a client know the number of allowed remaining requests before being throttled? The answer lies in HTTP response headers. The rate limiter returns the following HTTP headers to clients:

    X-Ratelimit-Remaining: The remaining number of allowed requests within the window.

    X-Ratelimit-Limit: It indicates how many calls the client can make per time window.

    X-Ratelimit-Retry-After: The number of seconds to wait until you can make a request again without being throttled.


When a user has sent too many requests, a 429 too many requests error and X-Ratelimit-Retry-After header are returned to the client.


![image](https://user-images.githubusercontent.com/23625821/132287806-04de0d48-0056-485e-b809-0e06ddec791d.png)

- Rules are stored on the disk. Workers frequently pull rules from the disk and store them in the cache.
- When a client sends a request to the server, the request is sent to the rate limiter middleware first.
- Rate limiter middleware loads rules from the cache. It fetches counters and last request timestamp from Redis cache. 

- Based on the response, the rate limiter decides:
    - if the request is not rate limited, it is forwarded to API servers.
    - if the request is rate limited, the rate limiter returns 429 too many requests error to the client. 
    - In the meantime, the request is either dropped or forwarded to the queue.



### Monitoring

After the rate limiter is put in place, it is important to gather analytics data to check whether the rate limiter is effective. Primarily, we want to make sure:
  - The rate limiting algorithm is effective.
  - The rate limiting rules are effective.

- For example, if rate limiting rules are too strict, many valid requests are dropped. In this case, we want to relax the rules a little bit. 
- In another example, we notice our rate limiter becomes ineffective when there is a sudden increase in traffic like flash sales. 
- In this scenario, we may replace the algorithm to support burst traffic. Token bucket is a good fit here.





## Step 4 - Machine Coding



### Design Patterns

- Strategy Pattern: Allows for flexibility in changing rate-limiting algorithms without modifying the client code.

- Singleton Pattern: Ensures only one instance of the rate limiter exists, maintaining a consistent state.

- Factory Pattern: Encapsulates the creation logic for different rate-limiting strategies, promoting clean code and adherence to the Open/Closed principle.


### Multiple Algorithms :
- Fixed Window Algorithm: Counts the number of requests in fixed time windows.

- Sliding Window Algorithm: Uses a rolling time window to count requests.

### RateLimiter Interface

```c++
public interface RateLimiter {
    boolean allowRequest(String clientId);
}
```

### FixedWindowRateLimiter Class

```c++
import java.util.HashMap;
import java.util.Map;

public class FixedWindowRateLimiter implements RateLimiter {
    private final int maxRequests;
    private final long windowSizeInMillis;
    private Map<String, Integer> requestCounts;
    private Map<String, Long> windowStartTimes;

    public FixedWindowRateLimiter(int maxRequests, long windowSizeInMillis) {
        this.maxRequests = maxRequests;
        this.windowSizeInMillis = windowSizeInMillis;
        this.requestCounts = new HashMap<>();
        this.windowStartTimes = new HashMap<>();
    }

    @Override
    public boolean allowRequest(String clientId) {
        long currentTime = System.currentTimeMillis();
        windowStartTimes.putIfAbsent(clientId, currentTime);
        requestCounts.putIfAbsent(clientId, 0);

        long windowStartTime = windowStartTimes.get(clientId);
        if (currentTime - windowStartTime >= windowSizeInMillis) {
            windowStartTimes.put(clientId, currentTime);
            requestCounts.put(clientId, 0);
        }

        int requestCount = requestCounts.get(clientId);
        if (requestCount < maxRequests) {
            requestCounts.put(clientId, requestCount + 1);
            return true;
        }
        return false;
    }
}
}
```

### SlidingWindowRateLimiter Class

```c++
import java.util.Map;
import java.util.HashMap;
import java.util.Queue;
import java.util.LinkedList;

public class SlidingWindowRateLimiter implements RateLimiter {
    private final int maxRequests;
    private final long windowSizeInMillis;
    private Map<String, Queue<Long>> requestTimestamps;

    public SlidingWindowRateLimiter(int maxRequests, long windowSizeInMillis) {
        this.maxRequests = maxRequests;
        this.windowSizeInMillis = windowSizeInMillis;
        this.requestTimestamps = new HashMap<>();
    }

    @Override
    public boolean allowRequest(String clientId) {
        long currentTime = System.currentTimeMillis();
        requestTimestamps.putIfAbsent(clientId, new LinkedList<>());

        Queue<Long> timestamps = requestTimestamps.get(clientId);
        while (!timestamps.isEmpty() && currentTime - timestamps.peek() > windowSizeInMillis) {
            timestamps.poll();
        }

        if (timestamps.size() < maxRequests) {
            timestamps.add(currentTime);
            return true;
        }
        return false;
    }
}
```


### RateLimiterFactory Class

```c++
public class RateLimiterFactory {
    public static RateLimiter createRateLimiter(String type, int maxRequests, long windowSizeInMillis) {
        switch (type.toLowerCase()) {
            case "fixed":
                return new FixedWindowRateLimiter(maxRequests, windowSizeInMillis);
            case "sliding":
                return new SlidingWindowRateLimiter(maxRequests, windowSizeInMillis);
            default:
                throw new IllegalArgumentException("Unknown rate limiter type");
        }
    }
}
```


### Singleton RateLimiterManager Class

```c++
public class RateLimiterManager {
    private static RateLimiterManager instance;
    private RateLimiter rateLimiter;

    private RateLimiterManager() {
        // Example initialization with a fixed window rate limiter
        this.rateLimiter = RateLimiterFactory.createRateLimiter("fixed", 100, 60000);
    }

    public static RateLimiterManager getInstance() {
        if (instance == null) {
            synchronized (RateLimiterManager.class) {
                if (instance == null) {
                    instance = new RateLimiterManager();
                }
            }
        }
        return instance;
    }

    public boolean allowRequest(String clientId) {
        return rateLimiter.allowRequest(clientId);
    }
}
```


### Main Class to Test the Implementation

```c++
public class Main {
    public static void main(String[] args) {
        RateLimiter fixedWindowRateLimiter = RateLimiterFactory.createRateLimiter("fixed", 10, 60000);
        RateLimiter slidingWindowRateLimiter = RateLimiterFactory.createRateLimiter("sliding", 10, 60000);

        // Testing Fixed Window Rate Limiter
        System.out.println("Fixed Window Rate Limiter:");
        for (int i = 0; i < 12; i++) {
            System.out.println(fixedWindowRateLimiter.allowRequest("client1"));
        }

        // Testing Sliding Window Rate Limiter
        System.out.println("Sliding Window Rate Limiter:");
        for (int i = 0; i < 12; i++) {
            System.out.println(slidingWindowRateLimiter.allowRequest("client2"));
        }
    }
}
```


### Explaination

- RateLimiter Interface: Defines the contract for any rate limiter.

- FixedWindowRateLimiter and SlidingWindowRateLimiter Classes: Implement the fixed window and sliding window rate-limiting algorithms.

- RateLimiterFactory Class: Provides a factory method to create instances of different rate limiters.

- RateLimiterManager Class: Implements the Singleton pattern to ensure a single instance of the rate limiter.


### Limitation of above design 

- Lack of Persistence: The current design doesn't persist the rate-limiting state. If the system restarts, all counters and timestamps will reset. This could lead to abuse if the service is restarted frequently.

- Single Point of Failure: The Singleton pattern used for RateLimiterManager introduces a single point of failure. If the instance is compromised or corrupted, it can affect the entire system's rate limiting.

- Scalability Issues: The current design is more suited for single-threaded environments. For multi-threaded or distributed systems, additional mechanisms are required to ensure consistency and scalability (e.g., using distributed data stores like Redis).

- Granularity of Configuration Updates: Updating the configuration applies globally to all clients. This design does not support per-client rate-limiting configuration, which might be necessary for more fine-grained control.



### Conclusion

Avoid being rate limited. Design your client with best practices:
  
  - Use client cache to avoid making frequent API calls.
  - Understand the limit and do not send too many requests in a short time frame.
  - Include code to catch exceptions or errors so your client can gracefully recover fromexceptions.
  - Add sufficient back off time to retry logic.


### References

<a href="https://www.amazon.com/System-Design-Interview-insiders-Second/dp/B08CMF2CQF"> System Design Interview </a>

Rate-limiting strategies and techniques: https://cloud.google.com/solutions/rate-limiting-strategies-techniques

Twitter rate limits: https://developer.twitter.com/en/docs/basics/rate-limits

Google docs usage limits: https://developers.google.com/docs/api/limits

IBM microservices: https://www.ibm.com/cloud/learn/microservices

Throttle API requests for better throughput: https://docs.aws.amazon.com/apigateway/latest/developerguide/api-gateway-request-throttling.html

Stripe rate limiters: https://stripe.com/blog/rate-limiters

Shopify REST Admin API rate limits: https://help.shopify.com/en/api/reference/rest-admin-api-rate-limits

Better Rate Limiting With Redis Sorted Sets: https://engineering.classdojo.com/blog/2015/02/06/rolling-rate-limiter/

System Design — Rate limiter and Data modelling:https://medium.com/@saisandeepmopuri/system-design-rate-limiter-and-data-modelling-9304b0d18250

How we built rate limiting capable of scaling to millions of domains: https://blog.cloudflare.com/counting-things-a-lot-of-different-things/

Redis website: https://redis.io/

Lyft rate limiting: https://github.com/lyft/ratelimit

Scaling your API with rate limiters: https://gist.github.com/ptarjan/e38f45f2dfe601419ca3af937fff574d#request-rate-limiter

What is edge computing: https://www.cloudflare.com/learning/serverless/glossary/what-is-edge-computing/

Rate Limit Requests with Iptables: https://blog.programster.org/rate-limit-requests-with-iptables
