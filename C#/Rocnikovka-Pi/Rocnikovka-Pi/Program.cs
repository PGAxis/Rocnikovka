using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Rocnikovka_Pi
{
    internal class Program
    {
        static void Main(string[] args)
        {
            double pi = 0.0;
            double iterations = 1000000000;

            Stopwatch sw = Stopwatch.StartNew();

            for (double i = 0; i < iterations; i++)
            {
                if (i % 2 == 0)
                {
                    pi += 1 / (2 * i + 1);
                }
                else
                {
                    pi -= 1 / (2 * i + 1);
                }
            }
            pi = pi * 4;

            sw.Stop();

            Console.WriteLine($"Approximation of Pi: {pi}, ticks it took (ms): {sw.ElapsedMilliseconds}");
            Console.ReadLine();
        }
    }
}
