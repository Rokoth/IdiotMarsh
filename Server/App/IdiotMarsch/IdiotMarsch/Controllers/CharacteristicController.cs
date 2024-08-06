using IdiotMarsch.Contract.Filters;
using IdiotMarsch.Contract.Interfaces;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Serilog.Core;
using System.Threading;
using System;
using System.Threading.Tasks;
using IdiotMarsch.Contract.Models;

namespace IdiotMarsch.Controllers
{
    [ApiController]
    [Route("api/characteristic")]
    [Authorize]
    [Produces("application/json")]
    public class CharacteristicController: Controller
    {
        private ICharacteristicDataService _characteristicDataService;
        private ILogger<CharacteristicController> _logger;

        public CharacteristicController(ILogger<CharacteristicController> logger, ICharacteristicDataService characteristicDataService) 
        {
            _characteristicDataService = characteristicDataService;
            _logger = logger;
        }

        [HttpGet("getlist")]
        public async Task<IActionResult> GetList(CharacteristicsFilter filter)
        {
            try
            {
                var userId = Guid.Parse(User.Identity.Name);
                var source = new CancellationTokenSource(30000);
                var result = await _characteristicDataService.GetAsync(filter, userId, source.Token);
                if (result.IsSuccess)
                    return Ok(result.Value);

                return StatusCode(StatusCodes.Status500InternalServerError, result.Message);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Ошибка при получении списка характеристик");
                return StatusCode(StatusCodes.Status500InternalServerError, ex.Message);
            }
        }

        [HttpPost("update")]
        public async Task<IActionResult> UpdateAsync(CharacteristicsUpdater updater)
        {
            try
            {
                var userId = Guid.Parse(User.Identity.Name);
                var source = new CancellationTokenSource(30000);
                var result = await _characteristicDataService.UpdateAsync(updater, userId, source.Token);
                if (result.IsSuccess)
                    return Ok(result.Value);

                return StatusCode(StatusCodes.Status500InternalServerError, result.Message);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Ошибка при обновлении характеристики");
                return StatusCode(StatusCodes.Status500InternalServerError, ex.Message);
            }
        }

        [HttpGet("get")]
        public async Task<IActionResult> Get(Guid id)
        {
            try
            {
                var userId = Guid.Parse(User.Identity.Name);
                var source = new CancellationTokenSource(30000);
                var result = await _characteristicDataService.GetAsync(id, userId, source.Token);
                if (result.IsSuccess)
                    return Ok(result.Value);

                return StatusCode(StatusCodes.Status500InternalServerError, result.Message);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Ошибка при получении характеристики");
                return StatusCode(StatusCodes.Status500InternalServerError, ex.Message);
            }
        }
    }
}
