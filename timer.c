struct timer {
    Delay       tick;
    Task        task;
    MessageId   id;
    Message     message;
    struct list_head list;
};

#define NR_WHEEL       (6)     
#define TICK_WHEEL     (64)

struct timing_wheel
{
    int    pointer;                        /* current pointer */
    struct list_head timers[TICK_WHEEL];   /* timer list */
};

static struct timing_wheel wheels[NR_WHEEL];
static time_t current_tick;

static time_t get_time(void)
{
    struct timeval tv;
    gettimeofday( &tv,NULL);
    return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

static void wheel_insert(struct timer *timer, struct timing_wheel *wheel, int offset)
{
    offset = (wheel->pointer + offset) % TICK_WHEEL;
    list_add(&timer->list, wheel->timers + offset);
}

static void timer_insert(struct timer *timer)
{
    int i = 0;
    int offset = 0;
    time_t mult = 1;
    time_t max = TICK_WHEEL;
    for(i = 0;i < NR_WHEEL && timer->tick > max;i++) {
        timer->tick += wheels[i].pointer * mult;
        mult = max;
        max *= TICK_WHEEL;
    }

    offset = timer->tick / mult;
    timer->tick -= (offset * mult);

    wheel_insert(timer, wheels + i, offset);
}

static void timer_init(void)
{
    for(int i = 0;i < NR_WHEEL;i++) {
        wheels[i].pointer = 0;
        for(int j = 0;j < TICK_WHEEL;j++) {
            INIT_LIST_HEAD(wheels[i].timers + j);
        }
    }
}

static void timer_tick(void)
{
    struct timing_wheel *wheel = NULL;
    for(int i = 0;i < NR_WHEEL;i++) {
        wheel = wheels + i;
        wheel->pointer = (wheel->pointer + 1) % TICK_WHEEL;
        list_for_each_safe(pos, next, wheel->timers + wheel->pointer) {
            list_del(pos);
            struct timer *timer = container_of(pos, struct timer, list);
            if(timer->tick) {
                timer_insert(timer);
            } else {
                MessageSend(timer->task, timer->id, timer->message);
                free(timer);
            }
        }
        if(wheel->pointer)
            break;
    }
}

