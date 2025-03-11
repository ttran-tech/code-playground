from datetime import datetime, timedelta
from typing import List, Dict
from itertools import filterfalse
import re, traceback, random, json


DAYS_PER_WEEK = 7
SEC_PER_HOUR = 3600


class FormatError(Exception):
    pass


def generate_commit_dates(start_date:str, end_date:str, min_active_days_per_week:int, max_active_days_per_week:int, start_hour:int, end_hour:int, min_commit_per_day:int, max_commit_per_day:int) -> Dict[str, List[str]]:
    """Generate a commit dates dictionary and pair each entry with a list commit hours."""
    
    def _generate_active_dates(start_date:str, end_date:str, min_active_days_per_week:int, max_active_days_per_week:int) -> List[str]:
        """Generate a list of active dates"""
        DATE_REGEX_PATTERN = r'^(\d{4})-(\d{2})-(\d{2})$'
        if not bool(re.match(DATE_REGEX_PATTERN, start_date)) or not bool(re.match(DATE_REGEX_PATTERN, end_date)):
            raise FormatError('Invalid date format. Date format must match "YYYY-MM-DD". Example: 2025-01-01')
        
        if start_date == end_date:
            raise FormatError('Invalid date range: The start date and end date cannot be the same')

        DATE_FORMAT = '%Y-%m-%d'
        start_date = datetime.strptime(f"{start_date}", DATE_FORMAT)
        end_date = datetime.strptime(f"{end_date}", DATE_FORMAT)

        day_total = (end_date - start_date).days + 1 # get total days in range

        # Get the number of weeks between the start and end date
        week_total = day_total // DAYS_PER_WEEK + (1 if day_total % DAYS_PER_WEEK else 0) # count partial week
        print(f" [+] Week Total: {week_total} | Total Days: {day_total}")

        # active_date = []
        active_dates = set()
        next_start_date = start_date
        for _ in range(week_total):
            week_end = min(next_start_date + timedelta(days=DAYS_PER_WEEK - 1), end_date) # handle last week
            days_in_week = (week_end - next_start_date).days + 1

            # Ensure at least 3 ~ 6 active days per week dynamically
            adjusted_min_days = max(min_active_days_per_week, min(3, days_in_week // 2))
            adjusted_max_days = min(max_active_days_per_week, days_in_week)
            active_date_per_week = random.randint(adjusted_min_days, adjusted_max_days)
            
            dates = [(next_start_date + timedelta(days=n)) for n in range(days_in_week)]
            for _ in range(active_date_per_week):
                # Use filterfalse to eliminate the elements already in active_dates, 
                # and create a list of available dates
                available_dates = list(filterfalse(active_dates.__contains__, dates))
                if available_dates:
                    date = random.choice(available_dates).strftime(DATE_FORMAT)
                    active_dates.add(date)

            next_start_date = week_end + timedelta(days=1) # move to next week
        return sorted(active_dates)

    def _generate_commit_hours(active_dates:List[datetime], start_hour:int, end_hour:int, min_commit_per_day:int, max_commit_per_day:int) -> Dict[str,List[str]]:
        """Generate commit hours per date"""
        commit_dates = {}
        for active_date in active_dates:
            commit_hours = []
            commit_per_day = random.randint(min_commit_per_day, max_commit_per_day-1) # exlude the last hour
            for i in range(commit_per_day):
                hour = random.randint(start_hour, end_hour)
                minute = random.randint(0, 59)
                second = random.randint(0, 59)
                commit_hours.append(f"{hour:02d}:{minute:02d}:{second:02d}")
            commit_hours.sort()
            commit_dates[active_date] = commit_hours
        return commit_dates
    
    try:
        active_dates = _generate_active_dates(start_date, end_date, min_active_days_per_week, max_active_days_per_week)
        commit_dates = _generate_commit_hours(active_dates, start_hour, end_hour, min_commit_per_day, max_commit_per_day)
        return commit_dates
    except FormatError as e:
        traceback.print_exc()
        return None


if __name__ == '__main__':
    start_date = '2023-01-01'
    end_date = '2023-02-01'
    min_active_days_per_week = 2
    max_active_days_per_week = 5
    start_hour = 8
    end_hour = 17
    min_commit_per_day = 1
    max_commit_per_day = 5
    commit_dates = generate_commit_dates(start_date, end_date, min_active_days_per_week, max_active_days_per_week, start_hour, end_hour, min_commit_per_day, max_commit_per_day)
    
    print(f"\t Total commit_dates: {len(commit_dates.keys())}")
    if commit_dates:
        commit_dates_json = json.dumps(commit_dates, indent=2)
        print(commit_dates_json)