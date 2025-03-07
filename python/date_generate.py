from datetime import datetime
import re, traceback

class FormatError(Exception):
    pass

def date_generate(start_date:str, end_date:str, start_hour:str, end_hour:str, min_active_days_per_week:int, max_active_days_per_week:int) -> list[datetime]:
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
    date_regex_pattern = r'^(\d{4})-(\d{2})-(\d{2})$'
    if not bool(re.match(date_regex_pattern, start_date)) or not bool(re.match(date_regex_pattern, end_date)):
        raise FormatError('Invalid date format. Date format must match "YYYY-MM-DD"')





if __name__ == '__main__':
    try:
        date_list = date_generate('2023-01-01', '2023-03-01', '08:00:00', '17:00:00', 2, 5)
        
        if date_list:
            for date in date_list:
                print(date)
    except FormatError as e:
        traceback.print_exc()