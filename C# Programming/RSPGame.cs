using System;

namespace rspGame
{
    internal class Program
    {
        class Game
        {
            private Random randomGenerator = new Random();

            public string cpuSelect;
            public string player;
            public string result;
            public int cpuWin = 0;
            public int playerWin = 0;
            public int count = 0;

            public string getCPUChoice()
            {
                var cpu = randomGenerator.Next(1, 4);

                return cpu switch
                {
                    1 => "가위",
                    2 => "바위",
                    _ => "보"
                };
            }

            public string getPlayerChoice()
            {
                Console.Write("가위, 바위, 보 중 입력해주세요 : ");
                return Console.ReadLine();
            }

            public string getMatchResult(string cpu, string player)
            {
                if (cpu == player) return "\n\n비겼습니다.\n\n";

                if ((cpu == "가위" && player == "바위") ||
                    (cpu == "바위" && player == "보") ||
                    (cpu == "보" && player == "가위"))
                {
                    playerWin++;
                    return "\n\n이겼습니다.\n\n";
                }

                if ((player == "가위" && cpu == "바위") ||
                    (player == "바위" && cpu == "보") ||
                    (player == "보" && cpu == "가위"))
                {
                    cpuWin++;
                    return "\n\n졌습니다.\n\n";
                }

                return "\n\n잘못된 값을 입력하였습니다. \n\n가위, 바위, 보 중에 입력해주세요.\n\n";
            }

            public bool IsGameContinued()
            {
                if (cpuWin == 3)
                {
                    Console.WriteLine("컴퓨터가 이겼습니다.\n");
                    return false;
                }
                else if (playerWin == 3)
                {
                    Console.WriteLine("플레이어가 이겼습니다.\n");
                    return false;
                }
                return true;
            }

            public void printResult()
            {
                Console.Clear();
                Console.WriteLine(" cpu : " + cpuSelect);
                Console.WriteLine(result + "\n\n");
                Console.WriteLine("컴퓨터가 이긴 횟수 : " + cpuWin);
                Console.WriteLine("플레이어가 이긴 횟수 : " + playerWin);
                Console.WriteLine("비긴 횟수 : " + count + "\n\n");
            }
        }

        static void Main(string[] args)
        {
            Game game = new Game();

            while (true)
            {
                game.cpuSelect = game.getCPUChoice();
                game.player = game.getPlayerChoice();

                game.result = game.getMatchResult(game.cpuSelect, game.player);
                game.printResult();

                if (!game.IsGameContinued())
                {
                    break;
                }
            }
        }
    }
}