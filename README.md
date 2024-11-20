This project is a C-based command-line utility that utilizes the cURL library to fetch content from a provided URL and save the response to a local file. It is designed to be highly customizable, allowing users to modify HTTP request headers, handle SSL verification, and save the content in different formats based on user input.

The tool accepts command-line arguments to define the URL, the output file, and optional arguments to modify headers or disable SSL verification, making it versatile for various HTTP request needs.

Key Features

- Fetch Data from URL: The tool sends HTTP requests to a specified URL and saves the response to a file.
- Customizable HTTP Headers: Users can specify custom headers such as User-Agent, Accept, and Authorization using command-line arguments.
- Header Debugging: You can enable a debugging mode that shows the custom headers being sent with the request.
- SSL Verification Control: The tool allows you to disable SSL verification for requests, useful for testing or when working with self-signed certificates.
- Default Header Behavior: If no custom headers are provided, default values are used for the headers (User-Agent: curl/7.79.1, Accept: * /*, and no Authorization).
- Error Handling: The program provides detailed error messages for incorrect usage or failed requests, including HTTP status codes and cURL error messages.

How It Works

Command-line Input: The program takes up to 3 arguments:
- URL: The target URL for fetching content.
- Output: The local file where the response will be saved.
- Arguments (optional):
  -HSET: Set custom headers for the request.
  -IGNORE: Ignore SSL certificate verification.
  -HDEBUG: Print debug information about the headers being sent.

Fetching the URL: Once the URL and output file are specified, the program sends an HTTP request to the provided URL and writes the response (HTML, JSON, etc.) to the specified file.

Custom Headers: If the -HSET argument is provided, users will be prompted to enter custom values for User-Agent, Accept, and Authorization. These values are then sent with the request.

SSL Verification: By default, SSL verification is enabled. However, if the -IGNORE argument is passed, SSL verification is skipped, making it useful for development and testing environments where self-signed certificates are used.

Error Handling and Response Status: The program checks the HTTP status code and informs the user if the request was successful or if there were any issues (e.g., 404 Not Found, 500 Internal Server Error).

Example Usage

Basic URL Fetch:
- ./http_fetcher https://example.com output.html
Fetches the content from https://example.com and saves it to output.html.

URL Fetch with Custom Headers:
- ./http_fetcher https://example.com output.html -HSET
Prompts the user to input custom headers (User-Agent, Accept, and Authorization) and sends them with the request.

URL Fetch with SSL Verification Disabled:
- ./http_fetcher https://example.com output.html -IGNORE
Fetches the content from the URL and saves it, but ignores SSL verification.

URL Fetch with Header Debugging:
- ./http_fetcher https://example.com output.html -HDEBUG
Prints the headers that will be sent with the request.

Requirements
- cURL: The cURL library is required to perform the HTTP requests.
- GCC or compatible C compiler: To compile and build the project.

Contributions are welcome! If you have improvements or bug fixes, feel free to fork the repository and submit a pull request.
This project is licensed under the MIT License
