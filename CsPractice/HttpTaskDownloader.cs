using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsPractice
{
    public class HttpTaskDownloader
    {
        public async Task<string> DownloadAsync(string url, CancellationToken token)
        {
            using HttpClient client = new HttpClient();
            using HttpResponseMessage response = await client.GetAsync(url, HttpCompletionOption.ResponseHeadersRead, token);
            response.EnsureSuccessStatusCode();
            using Stream contentStream = await response.Content.ReadAsStreamAsync(token);
            using MemoryStream memoryStream = new MemoryStream();
            await contentStream.CopyToAsync(memoryStream, token);
            return Encoding.UTF8.GetString(memoryStream.ToArray());
        }

        public async Task DownloadAnyAsync(IEnumerable<string> urls)
        {
            CancellationTokenSource cts = new CancellationTokenSource();

            List<Task<string>> downloadTasks = urls.Select(url => DownloadAsync(url, cts.Token)).ToList();
            await Task.WhenAny(downloadTasks);
            cts.Cancel(); // Cancel remaining tasks
        }

        [Test]
        public async Task TestDownloadAnyAsync()
        {
            var urls = new List<string>
            {
                "https://example.com/file1",
                "https://example.com/file2",
                "https://example.com/file3"
            };

            CancellationTokenSource cts = new CancellationTokenSource(TimeSpan.FromSeconds(10));
            var downloader = new HttpTaskDownloader();

            var task = downloader.DownloadAnyAsync(urls);
            await task;

            Assert.True(task.IsCompleted);
        }
    }
}