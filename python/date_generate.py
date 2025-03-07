from datetime import datetime, timedelta
import re, traceback, random, json


DAYS_PER_WEEK = 7
SEC_PER_HOUR = 3600


class FormatError(Exception):
    pass


def generate_commit_dates(start_date:str, end_date:str, min_active_days_per_week:int, max_active_days_per_week:int, start_hour:int, end_hour:int, min_commit_per_day:int, max_commit_per_day:int) -> dict[str, list[str]]:
    """
    Generate a list of date between two dates
    
    Parameters:
    start_date(str):    starting date, format as YYYY-MM-DD
    end_date(str):      ending date, format as YYYY-MM-DD
    start_hour(str):    starting hour per date, format as hour:minutes:second
    end_hour(str):      ending hour per date, format as hour:minutes:second
    min_active_days_per_week(int): minimum active days per week, used for random function as the minimum value
    max_active_days_per_week(int): maximum active days per week, used for maximum value in random function

    Return:
    list[datetime]:     return a list of datetime objects
    """
    try:
        active_dates = generate_active_dates(start_date, end_date, min_active_days_per_week, max_active_days_per_week)
        commit_dates = generate_commit_hours(active_dates, start_hour, end_hour, min_commit_per_day, max_commit_per_day)
        return commit_dates
    except FormatError as e:
        traceback.print_exc()


def generate_active_dates(start_date:str, end_date:str, min_active_days_per_week:int, max_active_days_per_week:int) -> list[datetime]:
    """
    Generate a list of date between two dates
    
    Parameters:
    start_date(str):    starting date, format as YYYY-MM-DD
    end_date(str):      ending date, format as YYYY-MM-DD
    min_active_days_per_week(int): minimum active days per week, used for random function as the minimum value
    max_active_days_per_week(int): maximum active days per week, used for maximum value in random function

    Return:
    list[datetime]:     return a list of datetime objects
    """
    DATE_REGEX_PATTERN = r'^(\d{4})-(\d{2})-(\d{2})$'
    if not bool(re.match(DATE_REGEX_PATTERN, start_date)) or not bool(re.match(DATE_REGEX_PATTERN, end_date)):
        raise FormatError('Invalid date format. Date format must match "YYYY-MM-DD". Example: 2025-01-01')
    
    DATE_FORMAT = '%Y-%m-%d'
    start_date = datetime.strptime(f"{start_date}", DATE_FORMAT)
    end_date = datetime.strptime(f"{end_date}", DATE_FORMAT)
    week_total = int(((end_date - start_date).days) / DAYS_PER_WEEK)  # get the number of weeks between the start and end date
    
    active_dates = []
    next_start_date = start_date
    for i in range(week_total):
        active_date_per_week = random.randint(min_active_days_per_week, max_active_days_per_week)
        next_end_date = next_start_date + timedelta(days=DAYS_PER_WEEK)
        dates = [(next_start_date + timedelta(days=n)) for n in range((next_end_date - next_start_date).days + 1)]
        for j in range(active_date_per_week):
            while True:
                date = random.choice(dates).strftime(DATE_FORMAT)
                if date not in active_dates:
                    active_dates.append(date)
                    break
        next_start_date = next_end_date
    active_dates.sort()
    return active_dates


def generate_commit_hours(active_dates:list[datetime], start_hour:int, end_hour:int, min_commit_per_day:int, max_commit_per_day:int) -> dict[str,list[str]]:
    commit_dates = {}
    for active_date in active_dates:
        commit_hours = []
        commit_per_day = random.randint(min_commit_per_day, max_commit_per_day-1) # exlude the last hour
        for i in range(commit_per_day):
            hour = random.randint(start_hour, end_hour)
            minute = random.randint(1, 60)
            second = random.randint(1, 60)
            commit_hours.append(f"{hour:02d}:{minute:02d}:{second:02d}")
        commit_hours.sort()
        commit_dates[active_date] = commit_hours

    return commit_dates


if __name__ == '__main__':
    commit_dates = generate_commit_dates('2023-01-01', '2023-03-01', 2, 5, 8, 17, 1, 8)
    
    if commit_dates:
        commit_dates_json = json.dumps(commit_dates, indent=2)
        print(commit_dates_json)