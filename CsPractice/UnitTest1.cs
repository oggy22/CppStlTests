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
    }
}