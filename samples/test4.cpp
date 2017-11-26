//#define _WIN32 (1)
//#define WIN32 (1)
//#define _X86_ (1)
//#define X86 (1)
#include <SDKDDKVer.h>
#include <Windows.h>

#include <vector>
#include <string>
#include <fcntl.h>
#include <datetimeapi.h>
#include <conio.h>
#include <chrono>

//#include <Threadpoolapiset.h>
#include <experimental\resumable>
#include <future>


using namespace std;
using namespace std::experimental;

class sleep_for {
  static void CALLBACK  TimerCallback(PTP_CALLBACK_INSTANCE, void* Context, PTP_TIMER)
  {
    coroutine_handle<>::from_address(Context).resume();
  } 
  PTP_TIMER timer = nullptr; 
  std::chrono::system_clock::duration duration; 
  
  public: 
  explicit sleep_for(std::chrono::system_clock::duration d) : duration(d) {}
  bool await_ready() const
  {
    printf("in ready\n");
    return duration.count() <= 0;
  }
  void await_suspend(coroutine_handle<> h)
  {
    printf("in suspend\n");
    int64_t relative_count = -duration.count(); 
    timer = CreateThreadpoolTimer(TimerCallback, h.to_address(), 0); 
    SetThreadpoolTimer(timer, (PFILETIME)&relative_count, 0, 0);
  }

  void await_resume()
  {
    printf("in resume\n");
  }
  ~sleep_for()
  {
    if (timer) 
      CloseThreadpoolTimer(timer);
  }
};

static sleep_for CreateSleep()
{
  return sleep_for(std::chrono::microseconds(500));
}

static future<void> test()
{
  co_await CreateSleep();
}


int main(int argc, char* argv[])
{
  test();
  getch();
  return 0;
}
