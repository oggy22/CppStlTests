using System.Threading.Tasks;

namespace CsPractice
{
    public class Tests
    {
        [SetUp]
        public void Setup()
        {

        }

        public async Task<int> GetDataAsync()
        {
            await Task.Delay(2000); // Simulates I/O work
            return 42;
        }

        [Test]
        public async Task Test1()
        {
            TestContext.WriteLine($"{DateTime.Now}");
            int result = await GetDataAsync();
            TestContext.WriteLine($"{DateTime.Now} Result: {result}");
        }

        private static readonly HttpClient client = new HttpClient();

        [OneTimeTearDown]
        static public void TearDownAttribute()
        {
            client.Dispose();
        }

        public async Task GetExampleAsync(string url)
        {
            Console.WriteLine("From GetExampleAsync");
            string content = await client.GetStringAsync(url);
            Console.WriteLine(content.Substring(0, 20)); // Print first 100 chars
        }

        [Test]
        public async Task Test2()
        {
            Console.WriteLine("Starting Tests");
            await DoJob();
            Console.WriteLine("Ending Tests");
        }

        public async Task DoJob()
        {
            Console.WriteLine("Entering DoJob");
            Task task1 = GetExampleAsync("https://www.example.com/");
            Task task2 = GetExampleAsync("https://www.example.com/");
            Console.WriteLine("Before Task.WhenAll");
            //await Task.WhenAll(task1, task2);
            Console.WriteLine("All tasks completed");
        }

        [Test]
        public async Task WaitTasksOneByOne()
        {
            // Wait 3 tasks with different delays one by one
            List<Task> tasks = new List<Task>();
            tasks.Add(Task<int>.Delay(300).ContinueWith(t => 1));
            tasks.Add(Task<int>.Delay(100).ContinueWith(t => 2));
            tasks.Add(Task<int>.Delay(200).ContinueWith(t => 3));

            List<int> results = new List<int>();
            while (tasks.Count > 0)
            {
                Task<int> finished = (Task<int>)await Task<int>.WhenAny(tasks); // Block until one task finishes
                tasks.Remove(finished);
                Console.WriteLine($"Task result: {await finished} at {DateTime.Now}");
                results.Add(await finished);
            }
            Assert.That(results, Is.EqualTo(new List<int> { 2, 3, 1 }));
        }

        private async IAsyncEnumerable<int> GetPerfectNumbersAsync()
        {
            for (int i = 1; i < 10000; i++)
            {
                await Task.Yield(); // Yield control to allow other work to run

                // Check if perfect numbers
                if (i == 6 || i == 28 || i == 496 || i == 8128)
                    yield return i;
            }
        }

        [Test]
        public async Task TestAsyncEnumerable()
        {
            await foreach (int number in GetPerfectNumbersAsync())
            {
                Console.WriteLine($"Perfect number: {number} at {DateTime.Now}");
            }
        }
    }
}