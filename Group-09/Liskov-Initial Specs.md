# **Write-up for Initial Class Development: Liskov**

### **Due: Jan 29, 2025**

For each of the assigned classes, you should include in your writeup:

1\) A **class description**, including what it’s goals are, and what it’s high-level functionality should look like. This does not need to perfectly match the description you were given, but it should be in the same general spirit unless you confirm any changes with the instructors ahead of time.

2\) A list of **similar classes** in the standard library that you should be familiar with or use to inform the functionality you will be developing.

3\) A list of **key functions** that you plan to implement. This does not need to be an exhaustive list, but it should give a strong indication of how the the class should be used.

4\) A set of **error conditions** that you will be responsive to. For each, indicate if it’s source was (1) *programmer error*, such as invalid arguments to a function, which should be caught by an assert, (2) a potentially *recoverable error*, such as a resource limitation, which should trigger an exception, or (3) a *user error*, such as invalid input, which needs to simply return a special condition for the programmer to respond to (note: these can usually be handled with exceptions as well if you prefer.)

5\) Any **expected challenges** that you will be facing, an especially any extra topics you need to learn about. This information will help me make sure to cover topics early in the course or else provide your group with extra guidance on the project.

6\) A list of any **other class projects** from other groups that you think you may want to use, either in the development of your own classes or in your final application.

### **Classes to Build**

| Class | Description |
| :---- | :---- |
| **EventQueue** | Track a series of events to trigger based on priority or time point; you should likely use a heap data structure to track which event is next. A user of the class should be able to request the timing of the next event (peeking at it without removing it), as well and pop the event out of the queue. If two events have the same timing, you should have a consistent method of breaking ties (perhaps by first added or by using secondary value) |
| **EventManager** | A handler for an EventQueue that can handle clock based timings to appropriately trigger events at appropriate times. An EventManager should also be able to deal with “repeating events” (putting them back in, as appropriate) when triggered, as well as pausing events. |
| **Image** | A representation of a web image; should maintain the URL of the image, its size, and eventually able to trigger JS code to put it on the web. It should also support alt text (for accessability) and fixed aspect ratios during resizing. |
| **TextBox** | Management object for a web-based version of a presentation text box. Should be able to hand bullet points, fonts and font-sizes, as both position and size of the box. One technique you may want use is the have two related functions: AddText(...) and AddRawText(...). The first of these will preserve any special characters (for example, converting a \< used into a \&lt; so it still appears correctly. The second does not alter the text, thus allowing the user to specify any HTML tags they want to use, but needing to appropriately encode things themselves. Other techniques are also possible, such as requiring a \\\\ before any tags to indicate that they should not be converted. |
| **WebLayout** | A manager for web pages, including what text or images are on the page and where they should go. Should be able to trigger the appropriate JavaScript code to set up the page and place any images or text boxes, as needed. You should decide of pages should be static or dynamic and how transitions between layouts should work. |

**EventQueue Class:**  
**Class Description:** A data structure to keep track of timing based events. Events will contain a timestamp, a unique id, and the data to be displayed. The highest priority (front) event in the queue is the event with the lowest time. Ties are broken in a first-in, first-out order.

**Similar Classes:** The main underlying data structure for the EventQueue will be a min-heap. EventQueue will likely use the std::priority\_queue.

**Key Functions:** 

- Add(time, data): Add an event to the queue. Return the event’s id.  
- Peek(): Return the event at the front of the queue.  
- Pop(): Remove the event at the front of the queue and return it.  
- Remove(id): Remove an event from the queue.  
- Clear(): Remove all events in the queue.  
- Size(): Return the current size of the queue.

**Error Conditions:**

1. Peeking/Popping an empty EventQueue  
   1. Programmer Error / User Error: Assert that the EventQueue has a Size() \> 0 before executing Peek/Pop.  
2. Invalid Arguments to Add()  
   1. Programmer Error: Assert that the event time is a numeric value \> 0\. Assert that the data parameter is a valid format.  
3. Removing a non-existent ID   
   1. User Error: Assert that Remove() is called with an ID that currently exists in the. Raise an exception.

**Expected Challenges:** The biggest expected challenge for this class will likely be tie-breaking. Another challenge will be coordinating/integrating with the EventManager class to implement the timing of the events and the structure of the data.

**Other Class Projects:** The Scheduler class from Group 7 could be useful, especially for the integration with EventManager. The ErrorManager class from Group 6 might also be useful for error reporting.  
 

**EventManager Class:**  
**Class Description**: A handler for EventQueue that tracks time and properly triggers events. It efficiently manages repeating events by reinserting them into the queue and ensures only active events are triggered, keeping track of paused events. Repeat events will be tracked using an event ID and repeat interval.

**Similar Classes**: Some useful classes to more thoroughly look into include std::chrono for time-handling capabilities, and various means of storing events such as std::unordered\_map and std::set.

**Key Functions:**

- PauseEvent(event id): Pauses future events  
- ResumeEvent(event id): Resumes paused events  
- AdvanceTime(): Advances internal time and checks for triggered events  
- TriggerEvent(event id): Triggers event, if repeat event adds it back to the queue

**Error Conditions:**

1\. Pausing/Resuming a Non-existent Event:

User Error: Return a special condition or exception to inform the user about the issue.

2\. Triggering an Incomplete Event:

Programmer Error: Use assertions to ensure event data is complete before triggering.

3\. Triggering a Non-existent Event:

Programmer Error: Throw an exception or log an error indicating the event is missing.

**Expected Challenges**:

The most likely challenge for this class will be properly dealing with time management and properly triggering events. It will also be important to efficiently store paused and repeating events.

**Other Class Projects**:

Group 4’s Assert could be useful for more complete error handling and Group 7’s Scheduler could help with efficient management of events.

**Image Class:**  
**Class Description:**  
The Image class is all about making it easy to add and manage images on a webpage. It keeps track of the image’s URL, size, and alt text while also making sure everything looks right when resized. One of the main goals is to let users dynamically place images using JavaScript.

**Similar Classes:**  
Classes and libraries relevant for developing this image representation include:

* Pillow (PIL): For handling image resizing while maintaining aspect ratios.  
* urllib: For validating and managing URLs of images.  
* JavaScript DOM manipulation: To insert images into web layouts dynamically.

**Key Functions:**

* \_\_init\_\_(url: str, width: int, height: int, alt\_text: str \= "")  
  * Constructor for creating an `Image` object with a URL, dimensions, and optional alt text.  
* render() \-\> str  
  * Generates and returns an HTML string for displaying the image on a webpage.  
* resize(width: int, height: int, maintain\_aspect: bool \= True)  
  * Resizes the image, with an option to maintain aspect ratio.  
* update\_alt\_text(new\_alt\_text: str)  
  * Updates the image’s alt text for accessibility purposes.  
* validate\_url() \-\> bool  
  * Checks if the image URL is valid and reachable.  
* generate\_js() \-\> str  
  * Creates a JavaScript snippet to dynamically add the image to the webpage.

**Error Conditions:**

1. Invalid URL provided  
   1. Programmer Error: The URL was not formatted correctly or left empty. This should be caught with an assertion.  
2. URL is unreachable  
   1. Recoverable Error: Raise an exception indicating that the image could not be loaded.  
3. Negative or zero dimensions provided  
   1. Programmer Error: Ensure dimensions are positive values using assertions.  
4. Resize results in invalid aspect ratio  
   1. User Error: If aspect ratio enforcement is enabled but new dimensions are incompatible, return an adjusted value instead of breaking the image.  
5. HTML/JS generation failure  
   1. Recoverable Error: If rendering code fails, raise an exception for debugging purposes.

**Expected Challenges:**  
One challenge will most likely be figuring out how to generate JavaScript from C++ to set up web pages and place images or text. Since I haven’t done that before, it’s going to be a learning experience just getting comfortable with how C++ can output and manage JavaScript code. Making sure everything actually works in a browser without breaking will probably take some trial and error.

**Other Class Projects:**  
Group 2’s ActionMap could be useful for handling dynamic interactions with images, such as triggering different JavaScript events when an image is clicked, hovered over, or resized. If we want users to be able to define image-related actions in the presentation system, this class could help.

**TextBox Class:**

**Class Description:** The **TextBox** class is responsible for managing a web-based text box that allows formatted text input for dynamic presentations. It should support adding text in two modes: escaped text (which converts special characters like `<` and `>` for safe display) and raw HTML (which allows inline HTML formatting). The class must also handle font customization, bullet points, and resizing while maintaining consistency in dynamic layouts. Additionally, it should correctly render text and bullet points, ensuring safe and structured HTML output.

**Similar Classes:**   
While there is no direct equivalent to TextBox in the standard library, the following C++ standard classes could be useful:

* std::string – For managing text content and applying formatting.  
* std::vector (or std::deque) – To store multiple lines of text or bullet points efficiently.  
* std::ostringstream – For constructing formatted HTML content before rendering.

**Key Functions:**

* TextBox(const TextBoxConfig& cfg);   
  * Initializes the text box with specified position, size, and style settings.  
* void addText(const std::string& text);  
  * Adds text while escaping special characters to ensure safe rendering in HTML.  
* void addRawText(const std::string& rawText);  
  * Adds raw HTML content without escaping, allowing inline HTML formatting.  
* void setStyle(const std::string& property, const std::string& value);  
  * Dynamically updates CSS properties like font size, color, or alignment.  
* void setPosition(int x, int y);  
  * Moves the text box to a new position on the page.  
* void resize(int width, int height);  
  * Adjusts the text box’s dimensions while ensuring proper text scaling.

**Error Conditions:** 

* **Invalid arguments** – Negative dimensions or invalid CSS properties (Programmer Error, handled with assertions).  
* **DOM creation failure** – Constraints in the web environment (Recoverable Error, throws std::runtime\_error).  
* **Excessively large input** – Prevents overly long text input (Recoverable Error, throws std::runtime\_error).  
* **Malformed raw HTML input** – Ensures invalid or unsafe HTML does not break rendering (User Error, throws std::invalid\_argument).  
* **Invalid position/size values** – Catches negative or out-of-range values (User Error, throws std::out\_of\_range).

**Expected Challenges:** A major challenge will be balancing text escaping and raw HTML formatting while keeping everything secure and rendering it properly. Dynamically managing bullet points and preventing issues when users edit content will also need close attention. On top of that, making sure WebAssembly works smoothly with the DOM will require some learning. Handling mixed input, like escaped text and raw HTML, while keeping the editing experience structured and easy to use, will be very important.

**Other Class Projects:** 

* Group 2: **ActionMap** – Could help map user interactions (e.g., button clicks) to functions that modify the text box dynamically.  
* Group 4: **RichText** – Would provide structured text formatting and parsing, simplifying inline HTML handling with functions like ToHtml() and ParseFromHtml(). This could improve text rendering and maintain security.  
* Group 5: **ExpressionParser** – Could enable dynamic evaluation of expressions within the text box for user-driven input.  
* Group 8: **DynamicString** – Could allow dynamic text updates that change based on external variables or user interactions.

**WebLayout Class:**  
   
**Class Description:** A manager for web pages that triggers javascript code to set up texts or images. Also handles options to transition between various pages. End goal is the ability to use this class to create a presentation by transitioning between different WebLayouts objects.

**Similar Classes:** Classes to get familiar with for the development of this web page manager would be string stream and string libraries. This would allow for reading and writing html code. Another class would be filesystem or file i/o streams for loading images if they are saved locally instead of online.

**Key Functions:** 

- TransitionToPage(): Will take in argument of another page and either dynamically or statically transition from the current page to the new page.  
- AddText(): Add a text element to the web page.  
- AddImage(): Add an image element to the web page.  
- RemoveText(): Remove a text element from the page.  
- RemoveImage(): Remove an image element from the page.  
- LoadPage(): Loads current page to the web by using javascript.  
- WebLayout(): Constructor for creating an web layout object  
- GenerateJS(): Generates javascript for current elements on the page.

**Error Conditions:**

4. Unable to create socket to website  
   1. Programmer Error: socket creation coded incorrectly or improper error catching sequence for failure  
5. HTML/Javascript generates incorrectly  
   1. Programmer Error: generate sequence has some error that causes the page to be generated corrupted  
6. Images/Text not loading correctly (Invalid Arguments when created)  
   1. User Error but Potentially Recoverable when creating objects for presentation slides. If the user puts an invalid url or file but the code can potentially have an alternative text or image file for failures.  
7. Trying to access deleted images/text boxes  
   1. Programmer Error: If an element gets deleted and not properly removed from the list of elements on the page, it may try to be accessed out of bounds.

**Expected Challenges:** One big expected challenge is implementing the ability to generate JavaScript code to set up the pages and place images or text. Personally, I have never used c++ to create JavaScript code so that will be a big learning experience. Another challenge is implementing the other classes in this project, such as Image, TextBox, and EventQueue in order to properly create the web pages. One challenge would be waiting for those implementations to be done, or them changing during development and having to change the WebLayout implementations of them.

**Other Class Projects:** One potential helpful class could be from Group 4, IndexSet, which holds indices from a container and could be useful for holding indices for image or text boxes. Also from that same group there is a better Assert statement function that would be helpful for debugging and testing.  
