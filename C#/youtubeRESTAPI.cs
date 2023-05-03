using Google.Apis.Services;
using Google.Apis.YouTube.v3;

// This program uses the Google.Apis.YouTube.v3 library to set up a YouTubeService object with an API key,
// and then executes a search request for the keyword "puppies". The search results are then printed out to the console

//to run replace "YOUR_API_KEY_HERE" with your actual YouTube API key
namespace YoutubeApiDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            // Set up the YouTube service
            var youtubeService = new YouTubeService(new BaseClientService.Initializer()
            {
                ApiKey = "YOUR_API_KEY_HERE",
                ApplicationName = "YoutubeApiDemo"
            });

            // Set up the search request
            var searchRequest = youtubeService.Search.List("snippet");
            searchRequest.Q = "puppies";
            searchRequest.MaxResults = 10;

            // Execute the search request
            var searchResponse = searchRequest.Execute();

            // Print out the search results
            foreach (var result in searchResponse.Items)
            {
                Console.WriteLine(result.Snippet.Title);
                Console.WriteLine(result.Snippet.Description);
                Console.WriteLine();
            }
        }
    }
}
