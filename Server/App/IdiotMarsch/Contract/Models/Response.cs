namespace IdiotMarsch.Contract.Models
{
    public class Response<T>
    {
        public T Value { get; private set; }

        public bool IsSuccess { get; private set; }

        public string Message { get; private set; }

        public static Response<T> Ok(T value)
        {
            return new Response<T>
            {
                Value = value,
                IsSuccess = true
            };
        }

        public static Response<T> Error(string message)
        {
            return new Response<T>
            {
                IsSuccess = false,
                Message = message
            };
        }
    }
}
