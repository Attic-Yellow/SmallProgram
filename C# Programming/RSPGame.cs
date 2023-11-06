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
                    1 => "����",
                    2 => "����",
                    _ => "��"
                };
            }

            public string getPlayerChoice()
            {
                Console.Write("����, ����, �� �� �Է����ּ��� : ");
                return Console.ReadLine();
            }

            public string getMatchResult(string cpu, string player)
            {
                if (cpu == player) return "\n\n�����ϴ�.\n\n";

                if ((cpu == "����" && player == "����") ||
                    (cpu == "����" && player == "��") ||
                    (cpu == "��" && player == "����"))
                {
                    playerWin++;
                    return "\n\n�̰���ϴ�.\n\n";
                }

                if ((player == "����" && cpu == "����") ||
                    (player == "����" && cpu == "��") ||
                    (player == "��" && cpu == "����"))
                {
                    cpuWin++;
                    return "\n\n�����ϴ�.\n\n";
                }

                return "\n\n�߸��� ���� �Է��Ͽ����ϴ�. \n\n����, ����, �� �߿� �Է����ּ���.\n\n";
            }

            public bool IsGameContinued()
            {
                if (cpuWin == 3)
                {
                    Console.WriteLine("��ǻ�Ͱ� �̰���ϴ�.\n");
                    return false;
                }
                else if (playerWin == 3)
                {
                    Console.WriteLine("�÷��̾ �̰���ϴ�.\n");
                    return false;
                }
                return true;
            }

            public void printResult()
            {
                Console.Clear();
                Console.WriteLine(" cpu : " + cpuSelect);
                Console.WriteLine(result + "\n\n");
                Console.WriteLine("��ǻ�Ͱ� �̱� Ƚ�� : " + cpuWin);
                Console.WriteLine("�÷��̾ �̱� Ƚ�� : " + playerWin);
                Console.WriteLine("��� Ƚ�� : " + count + "\n\n");
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