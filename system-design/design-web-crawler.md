# DESIGN A WEB CRAWLER

A web crawler is known as a robot or spider. It is widely used by search engines to discover new or updated content on the web. Content can be a web page, an image, a video, a PDF file, etc. A web crawler starts by collecting a few web pages and then follows links on those pages to collect new content. 

![image](https://user-images.githubusercontent.com/23625821/133965293-0d59d9e2-399d-4da2-aff3-67096ffe6136.png)

## Gneral features of a web crawler: 


- Scalability: The web is very large. There are billions of web pages out there. Web crawling should be extremely efficient using parallelization.
- Robustness: The web is full of traps. Bad HTML, unresponsive servers, crashes, malicious links, etc. are all common. The crawler must handle all those edge cases.

- Politeness: The crawler should not make too many requests to a website within a short time interval.
- Extensibility: The system is flexible so that minimal changes are needed to support new content types. For example, if we want to crawl image files in the future, we should not need to redesign the entire system.


## Workflow of a web crawler 

![image](https://user-images.githubusercontent.com/23625821/133965738-e1e85023-2646-49b0-9cf5-44335c4948d1.png)

Most important building components and techniques in depth:

- Depth-first search (DFS) vs Breadth-first search (BFS)
- URL frontier
- HTML Downloader

- Robustness
- Extensibility
- Detect and avoid problematic content

BFS is commonly used by web crawlers and is implemented by a first-in-first-out (FIFO) queue. In a FIFO queue, URLs are dequeued in the order they are enqueued. However, this implementation has two problems:

- Most links from the same web page are linked back to the same host. All the links in wikipedia.com are internal links, making the crawler busy processing URLs
from the same host (wikipedia.com). When the crawler tries to download web pages in parallel, Wikipedia servers will be flooded with requests. This is considered as “impolite”.

![image](https://user-images.githubusercontent.com/23625821/134113148-8a54f111-5154-41ea-8643-b74781e74e6e.png)

- Standard BFS does not take the priority of a URL into consideration. The web is large and not every page has the same level of quality and importance. Therefore, we may want to prioritize URLs according to their page ranks, web traffic, update frequency, etc.

- The general idea of enforcing politeness is to download one page at a time from the same host. 
- A delay can be added between two download tasks. 

- The politeness constraint is implemented by maintain a mapping from website hostnames to download (worker) threads.
- Each downloader thread has a separate FIFO queue and only downloads URLs obtained from that queue.

![image](https://user-images.githubusercontent.com/23625821/134287549-ac6e4a38-a5c0-4a6c-ae92-df3f8bff60f5.png)

- URLs are priotorized based on usefulness, which can be measured by PageRank, website traffic, update frequency, etc. 
- “Prioritizer” is the component that handles URL prioritization.
 
![image](https://user-images.githubusercontent.com/23625821/134287758-b52ca888-be1c-4bde-9330-baa3107c613d.png)

- Prioritizer: It takes URLs as input and computes the priorities.
- Queue f1 to fn: Each queue has an assigned priority. Queues with high priority are selected with higher probability.
- Queue selector: Randomly choose a queue with a bias towards queues with higher priority.

![image](https://user-images.githubusercontent.com/23625821/134287891-aee3cc4e-c067-413c-aa61-dd663509dfa8.png)


## CODE

### URL QUEUE (singleton pattern) :

```java
import java.util.LinkedList;
import java.util.Queue;

public class URLQueue {
    private static URLQueue instance;
    private Queue<String> queue;

    private URLQueue() {
        queue = new LinkedList<>();
    }

    public static synchronized URLQueue getInstance() {
        if (instance == null) {
            instance = new URLQueue();
        }
        return instance;
    }

    public synchronized void enqueue(String url) {
        if (!queue.contains(url)) {
            queue.add(url);
        }
    }

    public synchronized String dequeue() {
        return queue.poll();
    }

    public synchronized boolean isEmpty() {
        return queue.isEmpty();
    }
}
```

### HTTPClientFactory :

```java
public abstract class HTTPClient {
    public abstract String sendRequest(String url);
}

public class SimpleHTTPClient extends HTTPClient {
    @Override
    public String sendRequest(String url) {
        // Simulated HTTP request and response
        return "<html><head><title>Sample Page</title></head><body><a href=\"http://example.com/page1\">Link</a></body></html>";
    }
}

public class HTTPClientFactory {
    public static HTTPClient createHTTPClient() {
        return new SimpleHTTPClient();
    }
}
```


### PARSER

```java
import java.util.List;

public interface ParserStrategy {
    List<String> parse(String content);
}

public class HTMLParserStrategy implements ParserStrategy {
    @Override
    public List<String> parse(String content) {
        // Simulated HTML parsing
        List<String> urls = new ArrayList<>();
        if (content.contains("http://example.com/page1")) {
            urls.add("http://example.com/page1");
        }
        return urls;
    }
}
```


### CrawlerObserver


```java
public interface CrawlerObserver {
    void onNewURLProcessed(String url);
}

public class ConsoleObserver implements CrawlerObserver {
    @Override
    public void onNewURLProcessed(String url) {
        System.out.println("Processed URL: " + url);
    }
}
```


### CrawlCommand


```java
public class CrawlCommand {
    private String url;
    private HTTPClient httpClient;
    private ParserStrategy parser;
    private CrawlerObserver observer;

    public CrawlCommand(String url, HTTPClient httpClient, ParserStrategy parser, CrawlerObserver observer) {
        this.url = url;
        this.httpClient = httpClient;
        this.parser = parser;
        this.observer = observer;
    }

    public void execute() {
        String content = httpClient.sendRequest(url);
        List<String> urls = parser.parse(content);
        URLQueue queue = URLQueue.getInstance();
        for (String newUrl : urls) {
            queue.enqueue(newUrl);
        }
        observer.onNewURLProcessed(url);
    }
}
```


### WebCrawler

```java
import java.util.concurrent.TimeUnit;

public class WebCrawler {
    public static void main(String[] args) {
        URLQueue queue = URLQueue.getInstance();
        HTTPClient httpClient = HTTPClientFactory.createHTTPClient();
        ParserStrategy parser = new HTMLParserStrategy();
        CrawlerObserver observer = new ConsoleObserver();

        // Seed URL
        queue.enqueue("http://example.com");

        while (!queue.isEmpty()) {
            String url = queue.dequeue();
            if (url != null) {
                CrawlCommand command = new CrawlCommand(url, httpClient, parser, observer);
                command.execute();

                // Politeness policy: wait for 1 second between requests
                try {
                    TimeUnit.SECONDS.sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
```


## Summary of Features Implemented

- URL Queue: Implemented as a singleton to ensure a single queue instance.

- HTTP Client: Created using the Factory Pattern for flexibility.

- Parser: Strategy Pattern used to allow different parsing algorithms.

- Observer: Implemented to notify when a new URL is processed.

- Command: Encapsulates the crawling request, allowing for easy extension and logging.

- Breadth-First Search (BFS): Ensures broad exploration from the seed URL.

- Politeness Policy: Ensures a delay between requests to avoid server overload.



